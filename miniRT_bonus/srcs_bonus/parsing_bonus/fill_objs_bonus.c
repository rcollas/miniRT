#include "miniRT_bonus.h"

void	fill_sphere(t_parsing *var, char *line)
{
	int		i;

	i = 0;
	while (var->obj_info[i])
		i++;
	if (BONUS)
	{
		if (!check_error_param_texture(i, 4))
			exit_error_parsing(error(SPHERE_FORMAT_ERROR, line), NULL, var);
	}
	else if (i != 4)
		exit_error_parsing(error(SPHERE_FORMAT_ERROR, line), NULL, var);
	get_sphere_info(var, line, i);
}

void	fill_plane(t_parsing *var, char *line)
{
	int		i;

	i = 0;
	while (var->obj_info[i])
		i++;
	if (BONUS)
	{
		if (!check_error_param_texture(i, 4))
			exit_error_parsing(error(PLANE_FORMAT_ERROR, line), NULL, var);
	}
	else if (i != 4)
		exit_error_parsing(error(PLANE_FORMAT_ERROR, line), NULL, var);
	get_plane_info(var, line, i);
}

void	fill_cylinder(t_parsing *var, char *line)
{
	int		i;

	i = 0;
	while (var->obj_info[i])
		i++;
	if (BONUS)
	{
		if (!check_error_param_texture(i, 6))
			exit_error_parsing(error(CYLINDER_FORMAT_ERROR, line), NULL, var);
	}
	else if (i != 6)
		exit_error_parsing(error(CYLINDER_FORMAT_ERROR, line), NULL, var);
	get_cylinder_info(var, line, i);
}

void	fill_obj(int type, t_parsing *var, char *line)
{
	if (type == SPHERE)
		fill_sphere(var, line);
	if (type == PLANE)
		fill_plane(var, line);
	if (type == CYLINDER)
		fill_cylinder(var, line);
	if (type == DISK)
		fill_disk(var, line);
	if (type == CONE)
		fill_cone(var, line);
	if (type == SKY)
		fill_sky(var, line);
	if (type == SQUARE)
		fill_square(var, line);
}
