#include "../../incs/miniRT.h"

int	fill_rgb(char *rgb_values, t_rgb *rgb)
{
	char	**split_rgb;
	int 	i;

	i = 0;
	split_rgb = ft_split(rgb_values, ",");
	while (split_rgb[i])
		i++;
	if (i != 3)
		return (FAIL);
	rgb->r = ft_atoi(split_rgb[0]);
	rgb->g = ft_atoi(split_rgb[1]);
	rgb->b = ft_atoi(split_rgb[2]);
	return (SUCCESS);
}

int	fill_coordinates(char *coordinates_values, t_coord *coordinates)
{
	char **split_coordinates;
	int i;

	i = 0;
	split_coordinates = ft_split(coordinates_values, ",");
	while (split_coordinates[i])
		i++;
	if (i != 3)
		return (FAIL);
	coordinates->x = ft_atof(split_coordinates[0]);
	coordinates->y = ft_atof(split_coordinates[1]);
	coordinates->z = ft_atof(split_coordinates[2]);
	return (SUCCESS);
}

int	fill_vertex(char *vertex_values, t_vertex *vertex)
{
	char	**split_vertex;
	int 	i;

	i = 0;
	split_vertex = ft_split(vertex_values, ",");
	while (split_vertex[i])
		i++;
	if (i != 3)
		return (FAIL);
	vertex->x = ft_atof(split_vertex[0]);
	vertex->y = ft_atof(split_vertex[1]);
	vertex->z = ft_atof(split_vertex[2]);
	return (SUCCESS);
}



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
	fill_rgb(parsing->obj_info[2], ambient_light->rgb);
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
	fill_coordinates(parsing->obj_info[1], camera->coord);
	fill_vertex(parsing->obj_info[2], camera->vertex);
	camera->fov = ft_atoi(parsing->obj_info[3]);
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

void	fill_sphere(t_parsing *var, t_obj *obj, char *line)
{
	int	i;

	i = 0;
	while (var->obj_info[i])
		i++;
	if (i != 4)
	{
		error(SPHERE_FORMAT_ERROR, line);
		ft_exit_parsing(SPHERE_FORMAT_ERROR, var);
	}
	obj = new_obj(SPHERE, ft_atof(var->obj_info[2]), -1);
	fill_coordinates(var->obj_info[1], obj->coord);
	fill_rgb(var->obj_info[3], obj->rgb);
	if (check(obj, SPHERE) == FAIL)
	{
		error(SPHERE_FORMAT_ERROR, line);
		ft_exit_parsing(SPHERE_FORMAT_ERROR, var);
	}
}

void	fill_plan(t_parsing *var, t_obj *obj, char *line)
{
	int	i;

	i = 0;
	while (var->obj_info[i])
		i++;
	if (i != 4)
	{
		error(PLAN_FORMAT_ERROR, line);
		ft_exit_parsing(PLAN_FORMAT_ERROR, var);
	}
	obj = new_obj(PLAN, -1, -1);
	fill_vertex(var->obj_info[2], obj->vertex);
	fill_rgb(var->obj_info[3], obj->rgb);
	fill_coordinates(var->obj_info[1], obj->coord);
	if (check(obj, PLAN) == FAIL)
	{
		error(PLAN_FORMAT_ERROR, line);
		ft_exit_parsing(PLAN_FORMAT_ERROR, var);
	}
}

void	fill_cylinder(t_parsing *var, t_obj *obj, char *line)
{
	int	i;

	i = 0;
	while (var->obj_info[i])
		i++;
	if (i != 6)
	{
		error(CYLINDER_FORMAT_ERROR, line);
		ft_exit_parsing(CYLINDER_FORMAT_ERROR, var);
	}
	obj = new_obj(CYLINDER, ft_atof(var->obj_info[3]),
				  ft_atof(var->obj_info[4]));
	fill_vertex(var->obj_info[2], obj->vertex);
	fill_rgb(var->obj_info[5], obj->rgb);
	fill_coordinates(var->obj_info[1], obj->coord);
	if (check(obj, CYLINDER) == FAIL)
	{
		error(CYLINDER_FORMAT_ERROR, line);
		ft_exit_parsing(CYLINDER_FORMAT_ERROR, var);
	}
}

void	fill_obj(int type, t_parsing *var, char *line, t_obj *obj_list)
{
	t_obj	*obj;

	obj = NULL;
	if (type == SPHERE)
		fill_sphere(var, obj, line);
	if (type == PLAN)
		fill_plan(var, obj, line);
	if (type == CYLINDER)
		fill_cylinder(var, obj, line);
	obj_add_back(&obj_list, obj);
}

void	fill_structure(t_parsing *parsing_var)
{
	int		i;
	int		type;
	t_obj	*obj;

	i = 0;
	obj = NULL;
	while (parsing_var->input_list[i])
	{
		if (parsing_var->input_list[i][0] == '#')
			i++;
		else
		{
			parsing_var->obj_info = ft_split(parsing_var->input_list[i], "\t \r");
			type = is_valid_type(parsing_var->obj_info[0]);
			if (parsing_var->obj_info[0] && type == INVALID_TYPE_ERROR)
			{
				error(INVALID_TYPE_ERROR, parsing_var->input_list[i]);
				ft_exit_parsing(INVALID_TYPE_ERROR, parsing_var);
			}
			fill_scene(type, parsing_var, parsing_var->input_list[i]);
			fill_obj(type, parsing_var, parsing_var->input_list[i], obj);
			free_str_tab(parsing_var->obj_info);
			i++;
		}
	}
}
