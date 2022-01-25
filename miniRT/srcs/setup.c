#include "miniRT.h"

t_mlx	*setup_mlx(void)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)ft_calloc(1, sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return (NULL);
	mlx->window = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "Hello world!");
	if (!mlx->window)
		return (NULL);
	mlx->image = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	if (!mlx->image)
		return (NULL);
	mlx->addr = mlx_get_data_addr(mlx->image, &mlx->bpp,
			&mlx->size_line, &mlx->endian);
	mlx->bpp /= 8;
	return (mlx);
}

void	init_data(t_parsing *parsing_var, t_data *data)
{
	data->obj = parsing_var->objs;
	data->scene = parsing_var->scene;
	data->mlx = setup_mlx();
	if (!data->mlx)
		exit_error(data);
}
