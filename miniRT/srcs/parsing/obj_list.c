#include "miniRT.h"

t_obj	*last_obj(t_obj *obj_list)
{
	if (!obj_list)
		return (NULL);
	while (obj_list)
	{
		if (obj_list->next == NULL)
			return (obj_list);
		obj_list = obj_list->next;
	}
	return (obj_list);
}

void	obj_add_back(t_obj **obj_list, t_obj *to_add)
{
	t_obj	*last;

	if (!obj_list || !to_add)
		return ;
	if (*obj_list)
	{
		last = last_obj(*obj_list);
		last->next = to_add;
	}
	else
		*obj_list = to_add;
}

t_obj	*new_obj(int type, double diameter, double height)
{
	t_obj	*obj;

	obj = (t_obj *)ft_calloc(1, sizeof(t_obj));
	obj->type = type;
	obj->diameter = diameter;
	obj->height = height;
	obj->next = NULL;
	return (obj);
}