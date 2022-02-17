#include "miniRT.h"

void	display_cam_param(t_camera *camera)
{
	printf("Camera origin = {%.2f, %.2f, %.2f}\t", camera->up.coord[X],
		camera->up.coord[Y], camera->up.coord[Z]);
	printf("direction = {%.2f, %.2f, %.2f}\n", camera->origin->coord[X],
		camera->origin->coord[Y], camera->origin->coord[Z]);
}

void	display_info_move_cam(void)
{
	ft_putstr_fd("\n ----------------------------------------------------\n", 1);
	ft_putstr_fd("\033[38;5;215m To move the camera : ", 1);
	ft_putstr_fd("\t\tTo tilt the camera : \n\033[0m", 1);
	ft_putstr_fd("\033[38;5;229m ◦ x_axis : A D\t\t\t◦ left/right : ← →\n\033[0m", 1);
	ft_putstr_fd("\033[38;5;229m ◦ y_axis : SPACE MAJ\t\t", 1);
	ft_putstr_fd("◦ up/down    : ↑ ↓\n\033[0m", 1);
	ft_putstr_fd("\033[38;5;229m ◦ z_axis : W S\n\033[0m", 1);
	ft_putstr_fd(" ----------------------------------------------------\n\n", 1);
}
