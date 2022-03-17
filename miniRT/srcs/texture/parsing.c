#include "miniRT.h"

char	*copy_end_str(char *str, int length)
{
	int		str_length;
	char	*end;
	int		i;
	int		j;

	str_length = ft_strlen(str);
	if (!str || length > str_length)
		return (NULL);
	end = (char *)ft_calloc(1, sizeof(char) * (length + 1));
	i = str_length - length;
	j = 0;
	while (str && str[i])
		end[j++] = str[i++];
	end[j] = '\0';
	return (end);
}

_Bool	check_file_texture(char *filename)
{
	char	*texture;

	texture = copy_end_str(filename, 5);
	if (filename[0] == '\"' && texture
			&& ft_strcmp(texture, ".xpm\""))
		return (TRUE);
	return (FALSE);
}

_Bool	check_file_bump_map(char *filename)
{
	char	*normal_map;

	normal_map = copy_end_str(filename, 16);
	// printf("finename = %s | normal_map : %s\n", filename, normal_map);
	if (filename[0] == '\"' && normal_map
			&& ft_strcmp(normal_map, "_normal_map.xpm\""))
		return (TRUE);
	return (FALSE);
}

void	parse_texture(t_parsing *var, t_obj *obj, char *filename)
{
	if (!check_file_texture(filename))
		exit_error_parsing(INCORRECT_FILENAME, "incorrect filename (\"filename.xpm\")", var);
	open_texture(obj->texture, filename, var);
	obj->has_texture = NORMAL;
}

void	parse_bump_map(t_parsing *var, t_obj *obj, char *filename)
{
	if (!check_file_bump_map(filename))
		exit_error_parsing(INCORRECT_FILENAME,
			"incorrect filename (\"filename_normal_map.xpm\")", var);
	open_texture(obj->bump_map, filename, var);
	obj->has_texture = BUMP_MAP;
}

_Bool	check_error_param_texture(int i, int nb_ref)
{
	return (i == nb_ref || i == nb_ref + 1);
}

int	parse_param_texture(t_parsing *var, t_obj *obj, int i, int nb_ref)
{
	int		ret;
	_Bool	has_texture;

	has_texture = FALSE;
	ret = 0;
	if (var->obj_info[nb_ref - 1] && var->obj_info[nb_ref - 1][0] == '\"'
		&& obj->type != PLANE && obj->type != CONE)
	{
		parse_texture(var, obj, var->obj_info[nb_ref - 1]);
		has_texture = TRUE;
	}
	else
		ret += fill_rgb(var->obj_info[nb_ref - 1], obj->color);
	if (i == nb_ref + 1)
	{
		if (has_texture && var->obj_info[nb_ref] && var->obj_info[nb_ref][0] == '\"'
			&& obj->type != PLANE && obj->type != CONE)
			parse_bump_map(var, obj, var->obj_info[nb_ref]);
		else if (!has_texture)
			ret += parse_checker(obj, var->obj_info[nb_ref]);
		else
			ret++;
	}
	return (ret);
}
