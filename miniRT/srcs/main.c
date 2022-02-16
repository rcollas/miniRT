#include "miniRT.h"

void	exit_error(t_data *data)
{
	clean_data(data);
	exit(EXIT_FAILURE);
}

void	display_msg(void)
{
	ft_putstr_fd("\n ----------------------------------------------------\n", 1);
	ft_putstr_fd("\033[38;5;215m To move the camera : \t\tTo tilt the camera : \n\033[0m", 1);
	ft_putstr_fd("\033[38;5;229m x_axis : ← →\t\t\tleft/right : H J\n\033[0m", 1);
	ft_putstr_fd("\033[38;5;229m y_axis : ↑ ↓\t\t\tup/down    : K L\n\033[0m", 1);
	ft_putstr_fd("\033[38;5;229m z_axis : SPACE MAJ\n\033[0m", 1);
	ft_putstr_fd(" ----------------------------------------------------\n\n", 1);
	// printf("yaw = %f | pitch = %f\n", data->scene->camera->yaw_angle, data->scene->camera->pitch_angle);
}

int	main(int argc, char **argv)
{
	t_parsing	parsing_var[1];
	t_data		data[1];

	if (parsing(argv, argc, parsing_var) == FAIL)
		return (EXIT_FAILURE);
	init_data(parsing_var, data);
	init_euler_angles(data->scene->camera);
	display_msg();
	run_raytracing(data->mlx, data->scene, data, NO_PATH_TRACING);
	events_loop(data);
	print_list(data->obj);
	clean_data(data);
	return (0);
}
