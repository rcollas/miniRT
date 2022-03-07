#include "miniRT.h"

void	create_texture(t_ray *hit)
{
	t_image *texture;
	int		i;
	double	coord_uv[2];
	int		floor_uv[2];

	// if (hit->obj->type == DISK)
	// 	printf("width= %d | height = %d\n", hit->obj->texture->width, hit->obj->texture->height);

	texture = hit->obj->texture;
	hit->obj->get_uv_coord(*hit, coord_uv);
	coord_uv[U] = 1 - coord_uv[U];
	coord_uv[V] = 1 - coord_uv[V];
	floor_uv[U] = floor(coord_uv[U] * (texture->width - 1));
	floor_uv[V] = floor(coord_uv[V] * (texture->height - 1));
	i = floor_uv[V] * texture->line_len + floor_uv[U] * texture->bpp / 8;
	hit->color.coord[R] = (double)(unsigned char)texture->addr[i + 2] / 255;
	hit->color.coord[G] = (double)(unsigned char)texture->addr[i + 1] / 255;
	hit->color.coord[B] = (double)(unsigned char)texture->addr[i] / 255;
}

void	handle_texture(t_ray *hit)
{
	if (hit->obj->has_texture == CHECKER)
		create_checker(hit);
	if (hit->obj->has_texture == BUMP_MAP)
		create_texture(hit);
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

_Bool	check_file_texture(char *filename)
{
	int	length;

	length = ft_strlen(filename);
	if (length < 6)
		return (FALSE);
	if (!(filename[0] && filename[0] == '\"'
		&& filename[length - 1] && filename[length - 1] == '\"'))
		return (FALSE);
	if (!(filename[length - 5] && filename[length - 5] == '.'
		&& filename[length - 4] && filename[length - 4] == 'x'
		&& filename[length - 3] && filename[length - 3] == 'p'
		&& filename[length - 2] && filename[length - 2] == 'm'))
		return (FALSE);
	return (TRUE);
}

void	parse_texture(t_parsing *var, t_obj *obj, char *filename)
{
	if (!check_file_texture(filename))
		exit_error_parsing(INCORRECT_FILENAME, "incorrect filename", var);
	open_texture(obj->texture, filename, var);
	obj->has_texture = BUMP_MAP;
}
