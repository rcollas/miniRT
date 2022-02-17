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
	mlx->window = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "miniRT");
	if (!mlx->window)
		return (NULL);
	return (mlx);
}

void	init_image(t_mlx *mlx, t_data *data)
{
	t_image	*image;

	image = (t_image *)ft_calloc(1, sizeof(t_image));
	image->img_ptr = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	if (!image->img_ptr)
		exit_error(data);
	image->addr = mlx_get_data_addr(image->img_ptr, &image->bpp, &image->line_len, &image->endian);
	mlx->image = image;
}

void	init_data(t_parsing *parsing_var, t_data *data)
{
	data->obj = parsing_var->objs;
	data->scene = parsing_var->scene;
	data->mlx = setup_mlx();
	if (!data->mlx)
		exit_error(data);
}
