#include "miniRT.h"

void	fill_ambient_light(
	t_parsing *parsing, t_ambient_light *ambient_light, char *line)
{
	int				i;

	i = 0;
	while (parsing->obj_info[i])
		i++;
	if (i != 3 || parsing->ambient_light)
	{
		error(AMBIENT_LIGHT_FORMAT_ERROR, line);
		exit_error_parsing(AMBIENT_LIGHT_FORMAT_ERROR, NULL, parsing);
	}
	ambient_light->type = AMBIENT_LIGHT;
	ambient_light->intensity = ft_atof(parsing->obj_info[1]);
	fill_rgb(parsing->obj_info[2], ambient_light->color);
	if (check(ambient_light, AMBIENT_LIGHT) == FAIL)
	{
		error(AMBIENT_LIGHT_FORMAT_ERROR, line);
		exit_error_parsing(AMBIENT_LIGHT_FORMAT_ERROR, NULL, parsing);
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
		exit_error_parsing(CAMERA_FORMAT_ERROR, NULL, parsing);
	}
	camera->type = CAMERA;
	fill_coordinates(parsing->obj_info[1], camera->origin);
	fill_vertex(parsing->obj_info[2], camera->dir);
	camera->fov = ft_atoi(parsing->obj_info[3]) * M_PI / 180;
	if (check(camera, CAMERA) == FAIL)
	{
		error(CAMERA_FORMAT_ERROR, line);
		exit_error_parsing(CAMERA_FORMAT_ERROR, NULL, parsing);
	}
	parsing->camera = TRUE;
}

t_diffuse_light	*ft_realloc(t_parsing *parsing, t_diffuse_light *ptr)
{
	t_diffuse_light	*new_ptr;
	int				i;

	i = -1;
	if (parsing->light_nb == 1)
	{
		new_ptr = (t_diffuse_light *)ft_calloc(sizeof(t_diffuse_light), 1);
		if (!new_ptr)
			exit_error_parsing(MALLOC_ERROR, "malloc() failed", parsing);
	}
	else
	{
		new_ptr = (t_diffuse_light *) ft_calloc(sizeof(t_diffuse_light), parsing->light_nb);
		if (!new_ptr)
			exit_error_parsing(MALLOC_ERROR, "malloc() failed", parsing);
		while (ptr && ++i < parsing->light_nb)
		{
			copy_vec3(new_ptr[i].color, *ptr[i].color);
			copy_vec3(new_ptr[i].coord, *ptr[i].coord);
			new_ptr[i].type = ptr[i].type;
			new_ptr[i].intensity = ptr[i].intensity;
		}
		free(ptr);
	}
	return (new_ptr);
}

void	fill_diffuse_light(t_parsing *parsing, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = parsing->light_nb;
	parsing->light_nb++;
	while (parsing->obj_info[i])
		i++;
	if (i != 3)
	{
		ft_free(parsing->scene->diffuse_light);
		error(DIFFUSE_LIGHT_FORMAT_ERROR, line);
		exit_error_parsing(DIFFUSE_LIGHT_FORMAT_ERROR, NULL, parsing);
	}
	parsing->scene->diffuse_light = ft_realloc(parsing, parsing->scene->diffuse_light);
	parsing->scene->diffuse_light[j].type = DIFFUSE_LIGHT;
	fill_coordinates(parsing->obj_info[1], parsing->scene->diffuse_light[j].coord);
	parsing->scene->diffuse_light[j].intensity = ft_atof(parsing->obj_info[2]);
	if (check(&parsing->scene->diffuse_light[j], DIFFUSE_LIGHT) == FAIL)
	{
		ft_free(parsing->scene->diffuse_light);
		error(DIFFUSE_LIGHT_FORMAT_ERROR, line);
		exit_error_parsing(DIFFUSE_LIGHT_FORMAT_ERROR, NULL, parsing);
	}
	*parsing->scene->diffuse_light[j].color = create_vec3(1, 1, 1);
	parsing->diffuse_light = TRUE;
}

void	fill_scene(int type, t_parsing *var, char *line)
{
	if (type == AMBIENT_LIGHT)
		fill_ambient_light(var, var->scene->ambient_light, line);
	if (type == CAMERA)
		fill_camera(var, var->scene->camera, line);
	if (type == DIFFUSE_LIGHT)
		fill_diffuse_light(var, line);
}
