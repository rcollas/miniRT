#include "../../incs/miniRT.h"

void	obj_add_back(t_obj **obj_list, t_obj *to_add)
{
	int	i;

	i = 0;
	if (!*obj_list)
		*obj_list = to_add;
	else
	{
		while ((*obj_list)[i].next)
			i++;
		(*obj_list)[i].next = to_add;
	}
}

t_obj	*new_obj(int type, double diameter, double height)
{
	t_obj	*obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	obj->type = type;
	obj->diameter = diameter;
	obj->height = height;
	return (obj);
}