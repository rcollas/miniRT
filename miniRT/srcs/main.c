#include "miniRT.h"

int	main(int argc, char **argv)
{
	(void)argc;
	/*
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	(void)mlx_win;
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	mlx_loop(mlx);
	*/
	parsing(argv, argc);
	return (0);
}
