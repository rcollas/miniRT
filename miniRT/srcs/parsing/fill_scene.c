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

t_diffuse_light	*ft_realloc(t_diffuse_light *ptr, int size)
{
	t_diffuse_light	*new_ptr;
	int		i;

	i = 0;
	new_ptr = (t_diffuse_light *)ft_calloc(sizeof(t_diffuse_light), size);
	while (ptr && i < size)
	{
		copy_vec3(new_ptr[i].color, *ptr[i].color);
		copy_vec3(new_ptr[i].coord, *ptr[i].coord);
		new_ptr[i].type = ptr[i].type;
		new_ptr[i].intensity = ptr[i].intensity;
		i++;
	}
	free_tab((void **)&ptr, size - 1);
	return (new_ptr);
}

void	fill_diffuse_light(
	t_parsing *parsing, t_diffuse_light *diffuse_light, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = parsing->light_nb;
	if (j == 0)
		diffuse_light = (t_diffuse_light *)ft_calloc(sizeof(t_diffuse_light), 1);
	while (parsing->obj_info[i])
		i++;
	if (i != 3)
	{
		error(DIFFUSE_LIGHT_FORMAT_ERROR, line);
		ft_exit_parsing(DIFFUSE_LIGHT_FORMAT_ERROR, parsing);
	}
	if (j != 0)
		diffuse_light = ft_realloc(diffuse_light, parsing->light_nb + 1);
	diffuse_light[j].type = DIFFUSE_LIGHT;
	fill_coordinates(parsing->obj_info[1], diffuse_light[j].coord);
	diffuse_light[j].intensity = ft_atof(parsing->obj_info[2]);
	if (check(&diffuse_light[j], DIFFUSE_LIGHT) == FAIL)
	{
		error(DIFFUSE_LIGHT_FORMAT_ERROR, line);
		ft_exit_parsing(DIFFUSE_LIGHT_FORMAT_ERROR, parsing);
	}
	*diffuse_light[j].color = create_vec3(1, 1, 1);
	parsing->diffuse_light = TRUE;
	parsing->scene->diffuse_light = diffuse_light;
	parsing->light_nb++;
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
