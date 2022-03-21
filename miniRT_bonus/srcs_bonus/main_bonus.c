#include "miniRT_bonus.h"

int	main(int argc, char **argv)
{
	t_parsing	parsing_var[1];
	t_data		data[1];

	if (parsing(argv, argc, parsing_var) == FAIL)
		exit_error_parsing(MALLOC_ERROR, NULL, parsing_var);
	init_data(parsing_var, data);
	init_euler_angles(data->scene->camera);
	display_info_move_cam();
	run_minirt(data);
	events_loop(data);
	print_list(data->obj);
	clean_data(data);
	return (0);
}
