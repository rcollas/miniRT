#include "miniRT.h"

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
	safe_close(fd);
	return (SUCCESS);
}

void	fill_structure(t_parsing *parsing_var)
{
	int		i;
	int		type;

	i = 0;
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
			fill_obj(type, parsing_var, parsing_var->input_list[i]);
			free_str_tab(parsing_var->obj_info);
			i++;
		}
	}
}

void	parsing_var_init(t_parsing *var)
{
	var->camera = FALSE;
	var->diffuse_light = FALSE;
	var->ambient_light= FALSE;
	var->objs = NULL;
	var->obj_info = NULL;
	var->objs = NULL;
}

int	load_file(char **argv, int argc, int *fd)
{
	if (argc != 2)
	{
		parsing_error(ARG_NUMBER_ERROR, NULL);
		return (FAIL);
	}
	if (ft_open(argv[1], fd) != SUCCESS)
	{
		safe_close(*fd);
		return (FAIL);
	}
	if (is_valid_extension(argv[1]) == FALSE)
	{
		parsing_error(EXTENSION_ERROR, argv[1]);
		safe_close(*fd);
	}
	return (SUCCESS);
}

_Bool	file_is_complete(t_parsing *var, char *file)
{
	int	scene_objs;

	scene_objs = var->diffuse_light + var->ambient_light + var->camera;
	if (scene_objs != 3)
	{
		parsing_error(INCOMPLETE_FILE_ERROR, file);
		return (FAIL);
	}
	return (SUCCESS);
}

int	parsing(char **argv, int argc, t_parsing *parsing_var)
{
	int		fd;
	char	*input;

	input = NULL;

	parsing_var_init(parsing_var);
	if (load_file(argv, argc, &fd) == FAIL)
		return (FAIL);
	convert_file_to_string(fd, &input);
	parsing_var->input_list = ft_split(input, "\n");
	ft_free(input);
	fill_structure(parsing_var);
	if (file_is_complete(parsing_var, argv[1]) == FAIL)
		ft_exit_parsing(INCOMPLETE_FILE_ERROR, parsing_var);
	free_str_tab(parsing_var->input_list);
	return (SUCCESS);
}
