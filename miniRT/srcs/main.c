#include "miniRT.h"

void	exit_error(t_mlx *mlx)
{
	clean_mlx(mlx);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_mlx		*mlx;
	t_parsing	parsing_var[1];

	(void)mlx;
	(void)argc;
	(void)argv;
	parsing(argv, argc, parsing_var);
	mlx = setup_mlx();
	events_loop(mlx);
	print_list(parsing_var->objs);
	free_list(parsing_var->objs);
	return (0);
}
