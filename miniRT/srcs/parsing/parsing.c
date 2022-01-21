#include "miniRT.h"

_Bool	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1 && s1[i] && s2 && s2[i] && s1[i] == s2[i])
	{
		if (s1[i + 1] == 0 && s2[i + 1] == 0)
			return (EQUAL);
		i++;
	}
	return (DIFFERENT);
}

_Bool	is_valid_extension(char *arg)
{
	char *extension;

	extension = ft_strnstr(arg, ".rt", ft_strlen(arg));
	if (!extension || ft_strcmp(extension, ".rt") == DIFFERENT)
		return (FALSE);
	return (TRUE);
}

int	convert_file_to_string(int fd, char **input)
{
	int 	ret;
	char	buff[2];

	ret = 1;
	safe_ft_strdup(input, "", fd);
	while (ret > 0)
	{
		buff[1] = 0;
		ret = safe_read(fd, buff, 1, *input);
		if (ret > 0)
			safe_ft_strjoin(input, buff, fd);
	}
	return (SUCCESS);
}

int is_valid_type(char *type)
{
	if (ft_strcmp(type, "A") == EQUAL)
		return (AMBIENT_LIGHT);
	if (ft_strcmp(type, "L") == EQUAL)
		return (DIFFUSE_LIGHT);
	if (ft_strcmp(type, "C") == EQUAL)
		return (CAMERA);
	if (ft_strcmp(type, "sp") == EQUAL)
		return (SPHERE);
	if (ft_strcmp(type, "cy") == EQUAL)
		return (CYLINDER);
	if (ft_strcmp(type, "pl") == EQUAL)
		return (PLAN);
	return (INVALID_TYPE_ERROR);
}

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
	rgb = malloc(sizeof(t_rgb));
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
	split_coordinates = ft_split(coordinates_values, "," );
	while (split_coordinates[i])
		i++;
	if (i != 3)
		return (FAIL);
	coordinates = malloc(sizeof(t_coord));
	coordinates->x = atof(split_coordinates[0]);
	coordinates->y = atof(split_coordinates[1]);
	coordinates->z = atof(split_coordinates[2]);
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
	vertex = malloc(sizeof(t_vertex));
	vertex->x = atof(split_vertex[0]);
	vertex->y = atof(split_vertex[1]);
	vertex->z = atof(split_vertex[2]);
	return (SUCCESS);
}

void	fill_ambient_light(t_parsing *parsing, t_ambient_light *ambient_light, char *line)
{
	int	i;

	i = 0;
	while (parsing->obj_info[i])
		i++;
	if (i != 3 /*|| parsing->objs->ambient_light->rgb*/)
	{
		error(AMBIENT_LIGHT_FORMAT_ERROR, line);
		ft_exit_parsing(AMBIENT_LIGHT_FORMAT_ERROR, parsing);
	}
	ambient_light->type = AMBIENT_LIGHT;
	ambient_light->intensity = atof(parsing->obj_info[1]);
	fill_rgb(parsing->obj_info[2], ambient_light->rgb);
}

void	fill_camera(t_parsing *parsing, t_camera *camera, char *line)
{
	int	i;

	i = 0;
	while (parsing->obj_info[i])
		i++;
	if (i != 4 /*|| parsing->objs->camera->vertex*/)
	{
		error(AMBIENT_LIGHT_FORMAT_ERROR, line);
		ft_exit_parsing(AMBIENT_LIGHT_FORMAT_ERROR, parsing);
	}
	camera->type = CAMERA;
	fill_coordinates(parsing->obj_info[1], camera->coord);
	fill_vertex(parsing->obj_info[2], camera->vertex);
	camera->fov = ft_atoi(parsing->obj_info[3]);
}

void	fill_diffuse_light(t_parsing *parsing, t_diffuse_light *diffuse_light, char *line)
{

	int	i;

	i = 0;
	while (parsing->obj_info[i])
		i++;
	if (i != 4 /*|| parsing->objs->diffuse_light->coord*/)
	{
		error(AMBIENT_LIGHT_FORMAT_ERROR, line);
		ft_exit_parsing(AMBIENT_LIGHT_FORMAT_ERROR, parsing);
	}
	diffuse_light->type = DIFFUSE_LIGHT;
	fill_coordinates(parsing->obj_info[1], diffuse_light->coord);
	diffuse_light->intensity = atof(parsing->obj_info[2]);
}

void	fill_sphere(t_parsing *parsing, t_sphere *sphere, char *line)
{
	int	i;
	t_sphere	new_sphere;

	i = 0;
	while (parsing->obj_info[i])
		i++;
	if (i != 4)
	{
		error(AMBIENT_LIGHT_FORMAT_ERROR, line);
		ft_exit_parsing(AMBIENT_LIGHT_FORMAT_ERROR, parsing);
	}
	i = 0;
	new_sphere.type = SPHERE;
	fill_coordinates(parsing->obj_info[1], new_sphere.coord);
	new_sphere.diameter = atof(parsing->obj_info[2]);
	fill_rgb(parsing->obj_info[3], new_sphere.rgb);
	if (!sphere)
		sphere = &new_sphere;
	else
	{
		while (sphere[i].next)
			i++;
		sphere[i].next = &new_sphere;
	}
}

void	fill_plan(t_parsing *parsing, t_plan *plan, char *line)
{
	int	i;

	i = 0;
	t_plan	new_plan;
	while (parsing->obj_info[i])
		i++;
	if (i != 4)
	{
		error(AMBIENT_LIGHT_FORMAT_ERROR, line);
		ft_exit_parsing(AMBIENT_LIGHT_FORMAT_ERROR, parsing);
	}
	new_plan.type = PLAN;
	fill_coordinates(parsing->obj_info[1], new_plan.coord);
	fill_vertex(parsing->obj_info[2], new_plan.vertex);
	fill_rgb(parsing->obj_info[3], new_plan.rgb);
	i = 0;
	if (!plan)
		plan = &new_plan;
	else
	{
		while (plan[i].next)
			i++;
		plan[i].next = &new_plan;
	}
}

void	fill_cylinder(t_parsing *parsing, t_cylinder *cylinder, char *line)
{
	int	i;

	i = 0;
	t_cylinder	new_cylinder;
	while (parsing->obj_info[i])
		i++;
	if (i != 6)
	{
		error(AMBIENT_LIGHT_FORMAT_ERROR, line);
		ft_exit_parsing(AMBIENT_LIGHT_FORMAT_ERROR, parsing);
	}
	new_cylinder.type = CYLINDER;
	fill_coordinates(parsing->obj_info[1], new_cylinder.coord);
	fill_vertex(parsing->obj_info[2], new_cylinder.vertex);
	new_cylinder.diameter = atof(parsing->obj_info[3]);
	new_cylinder.height = atof(parsing->obj_info[4]);
	fill_rgb(parsing->obj_info[5], new_cylinder.rgb);
	i = 0;
	if (!cylinder)
		cylinder = &new_cylinder;
	else
	{
		while (cylinder[i].next)
			i++;
		cylinder[i].next = &new_cylinder;
	}
}

void	fill_by_type(int type, t_parsing *var, char *line)
{
	if (type == AMBIENT_LIGHT)
		fill_ambient_light(var, var->objs->ambient_light, line);
	if (type == CAMERA)
		fill_camera(var, var->objs->camera, line);
	if (type == DIFFUSE_LIGHT)
		fill_diffuse_light(var, var->objs->diffuse_light, line);
	if (type == SPHERE)
		fill_sphere(var, var->objs->sphere, line);
	if (type == PLAN)
		fill_plan(var, var->objs->plan, line);
	if (type == CYLINDER)
		fill_cylinder(var, var->objs->cylinder, line);
}

void	fill_structure(t_parsing *parsing_var)
{
	int		i;
	char	**obj_info;
	int		type;

	i = 0;
	while (parsing_var->input_list[i])
	{
		if (parsing_var->input_list[i][0] == '#')
			i++;
		else
		{
			obj_info = ft_split(parsing_var->input_list[i], "\t \r");
			parsing_var->obj_info = obj_info;
			type = is_valid_type(obj_info[0]);
			if (obj_info[0] && type == INVALID_TYPE_ERROR)
			{
				error(INVALID_TYPE_ERROR, parsing_var->input_list[i]);
				ft_exit_parsing(INVALID_TYPE_ERROR, parsing_var);
			}
			fill_by_type(type, parsing_var, parsing_var->input_list[i]);
			free_str_tab(obj_info);
			i++;
		}
	}
}

int	parsing(char **argv, int argc)
{
	int		fd;
	char	*input;
	t_obj	objs;
	t_parsing	parsing_var;

	input = NULL;
	parsing_var.objs = &objs;
	parsing_var.objs->camera = malloc(sizeof(t_camera));
	parsing_var.objs->ambient_light = malloc(sizeof(t_ambient_light));
	parsing_var.objs->diffuse_light = malloc(sizeof(t_diffuse_light));
	parsing_var.objs->cylinder = NULL;
	parsing_var.objs->sphere = NULL;
	parsing_var.objs->plan = NULL;
	if (argc != 2)
		return (parsing_error(ARG_NUMBER_ERROR, NULL));
	if (ft_open(argv[1], &fd) != SUCCESS)
	{
		safe_close(fd);
		return (FAIL);
	}
	if (is_valid_extension(argv[1]) == FALSE)
	{
		parsing_error(EXTENSION_ERROR, argv[1]);
		safe_close(fd);
	}
	convert_file_to_string(fd, &input);
	parsing_var.input_list = ft_split(input, "\n");
	ft_free(input);
	fill_structure(&parsing_var);
	return (SUCCESS);
}
