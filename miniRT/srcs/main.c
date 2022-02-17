#include "miniRT.h"

void	exit_error(t_data *data)
{
	clean_data(data);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_parsing	parsing_var[1];
	t_data		data[1];

	if (parsing(argv, argc, parsing_var) == FAIL)
		return (EXIT_FAILURE);
	init_data(parsing_var, data);
	init_euler_angles(data->scene->camera);
	display_info_move_cam();
	run_raytracing(data->mlx, data->scene, data, NO_PATH_TRACING);
	events_loop(data);
	print_list(data->obj);
	clean_data(data);
	return (0);
}
