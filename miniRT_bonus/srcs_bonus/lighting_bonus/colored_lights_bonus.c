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
		*light[i].color = create_vec3(1, 1, 1);
	}
	return (div_vec3_and_const(light_color, light_nb));
}

void	compute_obj_color(t_obj *obj, t_diffuse_light *light, int light_nb)
{
	int		i;
	t_vec3	new_color;
	t_vec3	light_color;

	i = -1;
	light_color = compute_light_color(light, light_nb);
	while (++i < obj->obj_nb)
	{
		copy_vec3(&new_color, *obj[i].color);
		new_color = add_vec3(new_color, light_color);
		new_color = div_vec3_and_const(new_color, 2);
		if (new_color.coord[R] > 1)
			new_color.coord[R] = 1;
		if (new_color.coord[G] > 1)
			new_color.coord[G] = 1;
		if (new_color.coord[B] > 1)
			new_color.coord[B] = 1;
		*obj[i].color = new_color;
	}
}
