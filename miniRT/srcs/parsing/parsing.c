#include "miniRT.h"

int	convert_file_to_string(int fd, char **input)
{
	int		ret;
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
				exit_error_parsing(INVALID_TYPE_ERROR, NULL, parsing_var);
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
	var->ambient_light = FALSE;
	var->objs = NULL;
	var->obj_info = NULL;
	var->objs = NULL;
	var->light_nb = 0;
	var->has_texture = FALSE;
	var->mlx = setup_mlx(var);
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

int	list_len(t_obj *obj)
{
	int	i;

	i = 0;
	while (obj)
	{
		i++;
		obj = obj->next;
	}
	return (i);
}

void	copy_texture(t_image *dest, t_image *src)
{
	dest->img_ptr = src->img_ptr;
	dest->addr = src->addr;
	dest->width = src->width;
	dest->height = src->height;
	dest->endian = src->endian;
	dest->bpp = src->bpp;
	dest->line_len = src->line_len;
}

t_obj	*list_to_tab(t_obj *obj, t_parsing *parsing_var)
{
	int		i;
	int		obj_nb;
	t_obj	*obj_tab;

	i = 0;
	obj_nb = list_len(obj);
	obj_tab = (t_obj *)ft_calloc(obj_nb, sizeof(t_obj));
	if (!obj_tab)
		exit_error_parsing(MALLOC_ERROR, "malloc failed()", parsing_var);
	while (obj)
	{
		obj_tab[i].type = obj->type;
		copy_vec3(obj_tab[i].origin, *obj->origin);
		copy_vec3(obj_tab[i].dir, *obj->dir);
		copy_vec3(obj_tab[i].color, *obj->color);
		copy_vec3(obj_tab[i].color_checker, *obj->color_checker);
		obj_tab[i].diameter = obj->diameter;
		obj_tab[i].height = obj->height;
		obj_tab[i].hit_object = obj->hit_object;
		obj_tab[i].get_uv_coord = obj->get_uv_coord;
		obj_tab[i].shine_factor = obj->shine_factor;
		obj_tab[i].obj_nb = obj_nb;
		copy_texture(obj_tab[i].texture, obj->texture);
		obj_tab[i].has_texture = obj->has_texture;
		i++;
		obj = obj->next;
	}
	free_list(obj);
	return (obj_tab);
}

void print_obj(t_parsing *parsing_var)
{
	int	i;

	i = 0;
	while (i < parsing_var->obj_nb)
	{
		if (parsing_var->objs[i].type == SPHERE)
			printf("-width = %d | height = %d\n",
				parsing_var->objs->texture->width, parsing_var->objs->texture->height);
		i++;
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
		exit_error_parsing(INCOMPLETE_FILE_ERROR, "incomplete file", parsing_var);
	free_str_tab(parsing_var->input_list);
	return (SUCCESS);
}
