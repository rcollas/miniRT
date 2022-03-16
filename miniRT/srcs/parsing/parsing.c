#include "miniRT.h"

void	parsing_var_init(t_parsing *var)
{
	var->camera = FALSE;
	var->diffuse_light = FALSE;
	var->ambient_light = FALSE;
	var->objs = NULL;
	var->obj_info = NULL;
	var->objs = NULL;
	var->light_nb = 0;
	var->has_texture = FALSE;
	var->mlx = setup_mlx(var);
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
				exit_error_parsing(INVALID_TYPE_ERROR, NULL, parsing_var);
			}
			fill_scene(type, parsing_var, parsing_var->input_list[i]);
			fill_obj(type, parsing_var, parsing_var->input_list[i]);
			free_str_tab(parsing_var->obj_info);
			i++;
		}
	}
}

int	parsing(char **argv, int argc, t_parsing *parsing_var)
{
	int		fd;
	char	*input;
	t_obj	*obj_tab;

	input = NULL;
	parsing_var_init(parsing_var);
	if (load_file(argv, argc, &fd) == FAIL)
		return (FAIL);
	convert_file_to_string(fd, &input);
	parsing_var->input_list = ft_split(input, "\n");
	ft_free(input);
	fill_structure(parsing_var);
	parsing_var->obj_nb = list_len(parsing_var->objs);
	obj_tab = list_to_tab(parsing_var->objs, parsing_var);
	parsing_var->objs = obj_tab;
	parsing_var->scene->light_nb = parsing_var->light_nb;
	if (file_is_complete(parsing_var, argv[1]) == FAIL)
		exit_error_parsing(
			INCOMPLETE_FILE_ERROR, "incomplete file", parsing_var);
	free_str_tab(parsing_var->input_list);
	return (SUCCESS);
}
