#include "miniRT.h"

void	exit_error(t_mlx *mlx)
{
	clean_mlx(mlx);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_mlx	*mlx;

	(void)mlx;
	(void)argc;
	(void)argv;
	// mlx = setup_mlx();
	// events_loop(mlx);
	parsing(argv, argc);
	return (0);
}
