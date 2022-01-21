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
	split_rgb = ft_split(rgb_values, ',');
	while (split_rgb[i])
		i++;
	if (i != 3)
		return (FAIL);
	rgb->r = ft_atoi(split_rgb[0]);
	rgb->g = ft_atoi(split_rgb[1]);
	rgb->b = ft_atoi(split_rgb[2]);
	return (SUCCESS);
}

void	fill_ambient_light(char **obj_info, t_obj *objs)
{
	t_ambient_light ambient_light;

	(void)objs;
	ambient_light.type = ft_atoi(obj_info[0]);
	ambient_light.intensity = atof(obj_info[1]);
	fill_rgb(obj_info[2], ambient_light.rgb);
}

void	fill_by_type(int type, char **obj_info, t_obj *objs)
{
	if (type == AMBIENT_LIGHT)
		fill_ambient_light(obj_info, objs);
	/*
	if (type == DIFFUSE_LIGHT)
		fill_diffuse_light(obj_info, objs);
	if (type == CAMERA)
		fill_camera(obj_info, objs);
	if (type == SPHERE)
		fill_sphere(obj_info, objs);
	if (type == CYLINDER)
		fill_cylinder(obj_info, objs);
	if (type == PLAN)
		fill_plan(obj_info, objs);
	 */
}

void	fill_structure(char **input_list, t_obj *objs)
{
	int		i;
	char	**obj_info;
	int		type;

	i = 0;
	while (input_list[i])
	{
		obj_info = ft_split(input_list[i], ' ');
		type = is_valid_type(obj_info[0]);
		if (type == INVALID_TYPE_ERROR)
			return (ft_putstr_fd("Error\n", 2));
		fill_by_type(type, obj_info, objs);
		i++;
	}
}

int	parsing(char **argv, int argc)
{
	int		fd;
	char	*input;
	char 	**input_list;
	t_obj	objs;

	input = NULL;
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
	input_list = ft_split(input, '\n');
	fill_structure(input_list, &objs);
	return (SUCCESS);
}
