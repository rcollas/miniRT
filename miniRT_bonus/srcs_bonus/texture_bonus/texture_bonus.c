#include "miniRT_bonus.h"

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
	ft_free(file);
	if (!texture->img_ptr)
		exit_error_parsing(MLX_ERROR, "mlx_xpm_file_to_image() failed", var);
	texture->addr = mlx_get_data_addr(texture->img_ptr, &texture->bpp,
			&texture->line_len, &texture->endian);
	if (!texture->img_ptr)
		exit_error_parsing(MLX_ERROR, "mlx_get_data_addr() failed", var);
}

t_vec2	transform_point_in_obj_space(
	t_vec3 hit_point, t_vec3 obj_origin, double max_dimension, t_vec3 obj_dir)
{
	t_vec2	new_point;

	normalize_vec3(&obj_dir);
	if (obj_dir.coord[X] == 1 || obj_dir.coord[X] == -1)
	{
		new_point.coord[X] = hit_point.coord[Z] - obj_origin.coord[Z];
		new_point.coord[X] /= max_dimension;
		new_point.coord[Y] = hit_point.coord[Y] - obj_origin.coord[Y];
		new_point.coord[Y] /= max_dimension;
	}
	else if (obj_dir.coord[Z] == 1 || obj_dir.coord[Z] == -1)
	{
		new_point.coord[X] = hit_point.coord[X] - obj_origin.coord[X];
		new_point.coord[X] /= max_dimension;
		new_point.coord[Y] = hit_point.coord[Y] - obj_origin.coord[Y];
		new_point.coord[Y] /= max_dimension;
	}
	else
	{
		new_point.coord[X] = hit_point.coord[X] - obj_origin.coord[X];
		new_point.coord[X] /= max_dimension;
		new_point.coord[Y] = hit_point.coord[Z] - obj_origin.coord[Z];
		new_point.coord[Y] /= max_dimension;
	}
	return (new_point);
}
