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
	texture->center.coord[X] = texture->width / 2.0;
	texture->center.coord[Y] = texture->height / 2.0;
}
