#include "miniRT.h"

_Bool	check_hit_object(
	t_ray *ray, t_obj *obj, t_ray *hit_min)
{
	t_ray	hit;

	if (obj->hit_object(ray, obj, &hit))
	{
		if (hit_min->dist > hit.dist)
		{
			hit_min->dist = hit.dist;
			hit_min->shine_factor = obj->shine_factor;
			copy_vec3(&hit_min->origin, hit.origin);
			copy_vec3(&hit_min->dir, hit.dir);
			copy_vec3(&hit_min->color, *obj->color);
		}
		return (TRUE);
	}
	return (FALSE);
}

void	init_var_hit(_Bool *hit_obj, t_ray *hit, t_vec3 *color)
{
	*hit_obj = FALSE;
	hit->dist = 1E99;
	hit->pixel_shadow = 1;
	hit->obj_ref = -1;
	*color = create_vec3(0, 0, 0);
}

void	detect_intersection(
	t_ray ray, unsigned long *color, t_data *data, t_thread *thread)
{
	_Bool	hit_obj;
	t_ray	hit;
	t_vec3	rgb;
	int		i;

	i = 0;
	init_var_hit(&hit_obj, &hit, &rgb);
	update_camera_ray(&ray, data, thread);
	while (i < data->obj_nb)
	{
		if (check_hit_object(&ray, &data->obj[i], &hit))
		{
			hit_obj = TRUE;
			hit.obj_ref = i;
		}
		i++;
	}
	if (hit_obj)
	{
		if (is_in_shadow(data->obj, hit, data->scene->diffuse_light))
			hit.pixel_shadow = SHADOW_COEFF;
		rgb = get_light(data, hit, ray);
	}
	*color = create_rgb_struct(&rgb);
}

void	clean_free(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	size_t	i;
	size_t	length;
	char	*dest;

	if (!s1)
		return (ft_strdup(s2));
	length = ft_strlen(s1) + ft_strlen(s2);
	dest = (char *)ft_calloc(1, sizeof(char) * (length + 1));
	if (!dest)
		return (NULL);
	i = -1;
	while (s1[++i])
		dest[i] = s1[i];
	while (*s2)
		dest[i++] = *s2++;
	dest[i] = '\0';
	clean_free(&s1);
	return (dest);
}

void	display_loading(t_data *data, t_thread *thread, int ratio, _Bool end)
{
	char	*msg;

	// ft_putstr_fd("\n\033[38;5;123mRendering with path_tracing...\n\n\033[0m", 1);
	if (data->path_tracing && data->multithreading && thread->id == THREADS - 1)
	{
		if (!end)
		{
			msg = ft_strdup("\r\033[38;5;123mRendering scene with path_tracing... [");
			msg = ft_strjoin_and_free(
					msg, ft_itoa(100 * (thread->pixel_y % ratio) / ratio));
			msg = ft_strjoin_and_free(msg, "%]\033[0m");
		}
		else
			msg = ft_strdup("\r\033[38;5;123mRendering scene with path_tracing... [100%]\033[0m\n\n");
		ft_putstr_fd(msg, 1);
		clean_free(&msg);
	}
}

void	run_raytracing(
	t_mlx *mlx, t_data *data, t_thread *thread)
{
	unsigned long	pixel_color;
	t_ray			cam_ray;
	int				ratio;

	ratio = HEIGHT / THREADS;
	init_camera_ray(&cam_ray, data);
	while (thread->pixel_y < thread->max_height)
	{
		thread->pixel_x = -1;
		while (++thread->pixel_x < WIDTH)
		{
			if (data->path_tracing)
				run_path_tracing(&cam_ray, &pixel_color, data, thread);
			else
				detect_intersection(cam_ray, &pixel_color, data, thread);
			draw_pixel(mlx->image, pixel_color, thread);
		}
		display_loading(data, thread, ratio, 0);
		thread->pixel_y++;
	}
	display_loading(data, thread, ratio, 1);
}

void	run_minirt(t_data *data)
{
	t_mlx		*mlx;
	t_thread	main_thread;

	mlx = data->mlx;
	init_image(mlx, data);
	data->cam_to_world_matrix = built_cam_to_world_matrix(data->scene->camera);
	if (data->multithreading)
		run_multithreading(data);
	else
	{
		main_thread.pixel_y = 0;
		main_thread.max_height = HEIGHT;
		run_raytracing(mlx, data, &main_thread);
	}
	display_cam_param(data->scene->camera);
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->image->img_ptr, 0, 0);
}
