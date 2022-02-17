#include "miniRT.h"

void	fill_ambient_light(t_parsing *parsing, t_ambient_light *ambient_light, char *line)
{
	int				i;

	i = 0;
	while (parsing->obj_info[i])
		i++;
	if (i != 3 || parsing->ambient_light)
	{
		error(AMBIENT_LIGHT_FORMAT_ERROR, line);
		ft_exit_parsing(AMBIENT_LIGHT_FORMAT_ERROR, parsing);
	}
	ambient_light->type = AMBIENT_LIGHT;
	ambient_light->intensity = ft_atof(parsing->obj_info[1]);
	fill_rgb(parsing->obj_info[2], ambient_light->color);
	if (check(ambient_light, AMBIENT_LIGHT) == FAIL)
	{
		error(AMBIENT_LIGHT_FORMAT_ERROR, line);
		ft_exit_parsing(AMBIENT_LIGHT_FORMAT_ERROR, parsing);
	}
	parsing->ambient_light = TRUE;
}

void	fill_camera(t_parsing *parsing, t_camera *camera, char *line)
{
	int			i;

	i = 0;
	while (parsing->obj_info[i])
		i++;
	if (i != 4 || parsing->camera)
	{
		error(CAMERA_FORMAT_ERROR, line);
		ft_exit_parsing(CAMERA_FORMAT_ERROR, parsing);
	}
	camera->type = CAMERA;
	fill_coordinates(parsing->obj_info[1], camera->origin);
	fill_vertex(parsing->obj_info[2], camera->dir);
	camera->fov = ft_atoi(parsing->obj_info[3]) * M_PI / 180;
	if (check(camera, CAMERA) == FAIL)
	{
		error(CAMERA_FORMAT_ERROR, line);
		ft_exit_parsing(CAMERA_FORMAT_ERROR, parsing);
	}
	parsing->camera = TRUE;
}

void	fill_diffuse_light(t_parsing *parsing, t_diffuse_light *diffuse_light, char *line)
{
	int	i;

	i = 0;
	while (parsing->obj_info[i])
		i++;
	if (i != 3 || parsing->diffuse_light)
	{
		error(DIFFUSE_LIGHT_FORMAT_ERROR, line);
		ft_exit_parsing(DIFFUSE_LIGHT_FORMAT_ERROR, parsing);
	}
	diffuse_light->type = DIFFUSE_LIGHT;
	fill_coordinates(parsing->obj_info[1], diffuse_light->coord);
	diffuse_light->intensity = ft_atof(parsing->obj_info[2]);
	if (check(diffuse_light, DIFFUSE_LIGHT) == FAIL)
	{
		error(DIFFUSE_LIGHT_FORMAT_ERROR, line);
		ft_exit_parsing(DIFFUSE_LIGHT_FORMAT_ERROR, parsing);
	}
	parsing->diffuse_light= TRUE;
}

void	fill_scene(int type, t_parsing *var, char *line)
{
	if (type == AMBIENT_LIGHT)
		fill_ambient_light(var, var->scene->ambient_light, line);
	if (type == CAMERA)
		fill_camera(var, var->scene->camera, line);
	if (type == DIFFUSE_LIGHT)
		fill_diffuse_light(var, var->scene->diffuse_light, line);
}
