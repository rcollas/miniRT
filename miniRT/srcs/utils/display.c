#include "miniRT.h"

void	display_cam_param(t_camera *camera)
{
	static int	even;

	if (even % 2 == 0)
		ft_putstr_fd(LIGHT_GREY, 1);
	else
		ft_putstr_fd(GREY, 1);
	printf("   {%-6.2f %6.2f %6.2f}\t", camera->origin->coord[X],
		camera->origin->coord[Y], camera->origin->coord[Z]);
	printf("{%-6.2f %6.2f %6.2f}\t", camera->dir->coord[X],
		camera->dir->coord[Y], camera->dir->coord[Z]);
	printf("\n");
	ft_putstr_fd(RESET, 1);
	even++;
}

void	display_info_move_cam(void)
{
	ft_putstr_fd("\n\t-----------------------------------------------------\n", 1);
	ft_putstr_fd("\t\033[38;5;215m To move the camera : ", 1);
	ft_putstr_fd("\t\tTo tilt the camera : \n", 1);
	ft_putstr_fd("\t\033[38;5;229m ◦ x_axis : A D\t\t\t◦ left/right : ← →\n", 1);
	ft_putstr_fd("\t\033[38;5;229m ◦ y_axis : SPACE MAJ\t\t", 1);
	ft_putstr_fd("◦ up/down    : ↑ ↓\n\033[0m", 1);
	ft_putstr_fd("\t\033[38;5;229m ◦ z_axis : W S\n", 1);
	ft_putstr_fd(RESET, 1);
	ft_putstr_fd(
		"\t-----------------------------------------------------\n\n\n", 1);
	ft_putstr_fd("        CAMERA ORIGIN\t\t   CAMERA DIRECTION\t\n", 1);
	ft_putstr_fd("  ___________________________________", 1);
	ft_putstr_fd("_____________________\n\n", 1);
}
