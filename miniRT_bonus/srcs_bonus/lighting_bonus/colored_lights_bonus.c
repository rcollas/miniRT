#include "miniRT_bonus.h"

t_vec3	compute_light_color(t_diffuse_light *light, int light_nb)
{
	t_vec3	light_color;
	int		i;

	i = -1;
	light_color = create_vec3(0, 0, 0);
	while (++i < light_nb)
	{
		light_color = add_vec3(light_color, *light[i].color);
	}
	check_limit_color(&light_color);
	return (light_color);
}

t_vec3	compute_obj_color(t_obj *obj, t_diffuse_light *light, int light_nb)
{
	int		i;
	t_vec3	light_color;
	t_vec3	obj_color;

	i = -1;
	light_color = compute_light_color(light, light_nb);
	while (++i < obj->obj_nb)
	{
		obj_color = mul_vec3(*obj[i].color, light_color);
		if (obj[i].has_texture == CHECKER)
			*obj[i].color_checker = mul_vec3(
					*obj[i].color_checker, light_color);
	}
	return (obj_color);
}
