#include "miniRT.h"

void	create_texture(t_ray *hit, t_image *texture, t_vec3 *color)
{
	t_vec2	uv;
	int		floor_uv[2];
	int		i;

	hit->obj->get_uv_coord(*hit, &uv);
	uv.coord[U] = 1 - uv.coord[U];
	uv.coord[V] = 1 - uv.coord[V];
	floor_uv[U] = floor(uv.coord[U] * (texture->width - 1));
	floor_uv[V] = floor(uv.coord[V] * (texture->height - 1));
	i = floor_uv[V] * texture->line_len + floor_uv[U] * texture->bpp / 8;
	color->coord[R] = (double)(unsigned char)texture->addr[i + 2] / 255;
	color->coord[G] = (double)(unsigned char)texture->addr[i + 1] / 255;
	color->coord[B] = (double)(unsigned char)texture->addr[i] / 255;
	// if (color->coord[R] > 0.01 && color->coord[G] > 0.01 && color->coord[B] > 0.01)
	// 	printf("%f  %f  %f\n", color->coord[R], color->coord[G], color->coord[B]);
}

void	mix_textures(
	t_ray *hit, t_image *texture_1, t_image *texture_2, t_vec3 *color)
{
	t_vec2	uv;
	int		floor_uv_1[2];
	int		floor_uv_2[2];
	int		i;
	int		j;

	hit->obj->get_uv_coord(*hit, &uv);
	uv.coord[U] = 1 - uv.coord[U];
	uv.coord[V] = 1 - uv.coord[V];
	floor_uv_1[U] = floor(uv.coord[U] * (texture_1->width - 1));
	floor_uv_1[V] = floor(uv.coord[V] * (texture_1->height - 1));
	floor_uv_2[U] = floor(uv.coord[U] * (texture_2->width - 1));
	floor_uv_2[V] = floor(uv.coord[V] * (texture_2->height - 1));

	i = floor_uv_1[V] * texture_1->line_len + floor_uv_1[U] * texture_1->bpp / 8;
	j = floor_uv_2[V] * texture_2->line_len + floor_uv_2[U] * texture_2->bpp / 8;

	color->coord[R] = (double)(unsigned char)texture_1->addr[i + 2] / 255;
	color->coord[G] = (double)(unsigned char)texture_1->addr[i + 1] / 255;
	color->coord[B] = (double)(unsigned char)texture_1->addr[i] / 255;
	color->coord[R] /= ((double)(unsigned char)texture_2->addr[i + 2] / 255 - 0.03);
	color->coord[G] /= ((double)(unsigned char)texture_2->addr[i + 1] / 255 - 0.03);
	color->coord[B] /= ((double)(unsigned char)texture_2->addr[i] / 255 - 0.03);
}

void	handle_texture(t_ray *hit)
{
	if (hit->obj->has_texture == CHECKER)
		create_checker(hit);
	else if (hit->obj->has_texture == NORMAL)
		create_texture(hit, hit->obj->texture, &hit->color);
	else if (hit->obj->has_texture == BUMP_MAP)
	{
		create_texture(hit, hit->obj->texture, &hit->color);
		apply_bump_map(hit);
		// mix_textures(hit, hit->obj->texture, hit->obj->bump_map, &hit->color);
	}
}

void	open_texture(t_image *texture, char *filename, t_parsing *var)
{
	char	*file;

	file = ft_strtrim(filename, "\"");
	texture->img_ptr = mlx_xpm_file_to_image(var->mlx->ptr, file,
			&texture->width, &texture->height);
	if (!texture->img_ptr)
		exit_error_parsing(MLX_ERROR, "mlx_xpm_file_to_image() failed", var);
	texture->addr = mlx_get_data_addr(texture->img_ptr, &texture->bpp,
			&texture->line_len, &texture->endian);
	if (!texture->img_ptr)
		exit_error_parsing(MLX_ERROR, "mlx_get_data_addr() failed", var);
}
