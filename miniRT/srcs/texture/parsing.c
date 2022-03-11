#include "miniRT.h"

_Bool	check_file_texture(char *filename)
{
	int	length;

	length = ft_strlen(filename);
	if (length < 6)
		return (FALSE);
	if (!(filename[0] && filename[0] == '\"'
			&& filename[length - 1] && filename[length - 1] == '\"'))
		return (FALSE);
	if (!(filename[length - 5] && filename[length - 5] == '.'
			&& filename[length - 4] && filename[length - 4] == 'x'
			&& filename[length - 3] && filename[length - 3] == 'p'
			&& filename[length - 2] && filename[length - 2] == 'm'))
		return (FALSE);
	return (TRUE);
}

void	parse_texture(t_parsing *var, t_obj *obj, char *filename)
{
	if (!check_file_texture(filename))
		exit_error_parsing(INCORRECT_FILENAME, "incorrect filename", var);
	open_texture(obj->texture, filename, var);
	obj->has_texture = NORMAL;
}

void	parse_bump_map(t_parsing *var, t_obj *obj, char *filename)
{
	if (!check_file_texture(filename))
		exit_error_parsing(INCORRECT_FILENAME, "incorrect filename", var);
	open_texture(obj->bump_map, filename, var);
	obj->has_texture = BUMP_MAP;
}

_Bool	check_error_param_texture(int i, int nb_ref)
{
	return (i == nb_ref || i == nb_ref + 1);
}

int	parse_param_texture(t_parsing *var, t_obj *obj, int i, int nb_ref)
{
	int	ret;

	ret = 0;
	if (var->obj_info[nb_ref - 1] && var->obj_info[nb_ref - 1][0] == '\"')
		parse_texture(var, obj, var->obj_info[nb_ref - 1]);
	else
		ret += fill_rgb(var->obj_info[nb_ref - 1], obj->color);
	if (i == nb_ref + 1)
	{
		if (var->obj_info[nb_ref] && var->obj_info[nb_ref][0] == '\"')
			parse_bump_map(var, obj, var->obj_info[nb_ref]);
		else
			ret += parse_checker(obj, var->obj_info[nb_ref]);
	}
	return (ret);
}
