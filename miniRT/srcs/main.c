#include "miniRT.h"

void	exit_error(t_mlx *mlx)
{
	clean_mlx(mlx);
	exit(EXIT_FAILURE);
}

int	main(void)
{
	t_mlx	*mlx;

	mlx = setup_mlx();
	events_loop(mlx);
	return (0);
}
