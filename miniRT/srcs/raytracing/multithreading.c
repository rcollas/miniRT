#include "miniRT.h"

void	*init_multithreading(void *void_thread)
{
	t_data		*data;
	t_thread	*thread;

	thread = (t_thread *)void_thread;
	data = (t_data *)thread->data;
	thread->pixel_y = HEIGHT / THREADS * thread->id;
	thread->max_height = HEIGHT / THREADS * (thread->id + 1);
	run_raytracing(data->mlx, data, thread);
	return (NULL);
}

void	*progress_bar(void *void_data)
{
	t_data		*data;

	data = (t_data *)void_data;
	while (data->multi_thread[0].pixel_y < data->multi_thread[0].max_height)
		printf("%d\n", data->multi_thread[0].pixel_y);
	return (NULL);
}

void	run_multithreading(t_data *data)
{
	int	i;

	i = 0;
	while (i < THREADS)
	{
		data->multi_thread[i].id = i;
		data->multi_thread[i].data = data;
		pthread_create(&data->multi_thread[i].thread, NULL,
			init_multithreading, (void *)&data->multi_thread[i]);
		i++;
	}
	i = 0;
	while (i < THREADS)
	{
		pthread_join(data->multi_thread[i].thread, NULL);
		i++;
	}
}
