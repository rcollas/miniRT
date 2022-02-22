#include "miniRT.h"

void	display_cam_param(t_camera *camera)
{
	printf("  \033[38;5;229mCamera origin = {%.2f, %.2f, %.2f}\t", camera->origin->coord[X],
		camera->origin->coord[Y], camera->origin->coord[Z]);
	printf("  dir = {%.2f, %.2f, %.2f}\033[0m\n", camera->dir->coord[X],
		camera->dir->coord[Y], camera->dir->coord[Z]);
}

void	display_info_move_cam(void)
{
	ft_putstr_fd("\n\t-----------------------------------------------------\n", 1);
	ft_putstr_fd("\t\033[38;5;215m To move the camera : ", 1);
	ft_putstr_fd("\t\tTo tilt the camera : \n\033[0m", 1);
	ft_putstr_fd("\t\033[38;5;229m ◦ x_axis : A D\t\t\t◦ left/right : ← →\n\033[0m", 1);
	ft_putstr_fd("\t\033[38;5;229m ◦ y_axis : SPACE MAJ\t\t", 1);
	ft_putstr_fd("◦ up/down    : ↑ ↓\n\033[0m", 1);
	ft_putstr_fd("\t\033[38;5;229m ◦ z_axis : W S\n\033[0m", 1);
	ft_putstr_fd("\t-----------------------------------------------------\n\n", 1);
}

void	print_list(t_obj *obj)
{
	int	i;

	i = 1;
	while (obj)
	{
		printf("-------OBJ %d--------\n", i);
		if (obj->type == SPHERE)
			printf("TYPE = SPHERE\n");
		if (obj->type == CYLINDER)
			printf("TYPE = CYLINDER\n");
		if (obj->type == PLANE)
			printf("TYPE = PLANE\n");
		if (obj->type == DISK)
			printf("TYPE = DISK\n");
		printf("RGB VALUE: R = %f\n", obj->color->coord[R]);
		printf("           G = %f\n", obj->color->coord[G]);
		printf("           B = %f\n", obj->color->coord[B]);
		printf("COORDINATES: X = %f\n", obj->origin->coord[X]);
		printf("             Y = %f\n", obj->origin->coord[Y]);
		printf("             Z = %f\n", obj->origin->coord[Z]);
		printf("DIAMETER VALUE = %f\n", obj->diameter);
		printf("HEIGHT VALUE = %f\n\n", obj->height);
		i++;
		obj = obj->next;
	}
}

void	print_matrix(t_matrix4 matrix)
{
	printf("row_1[x] = %f    row_1[y] = %f    row_1[z] = %f\n",
		matrix.row_1.coord[X], matrix.row_1.coord[Y], matrix.row_1.coord[Z]);
	printf("row_2[x] = %f    row_2[y] = %f    row_2[z] = %f\n",
		matrix.row_2.coord[X], matrix.row_2.coord[Y], matrix.row_2.coord[Z]);
	printf("row_3[x] = %f    row_3[y] = %f    row_3[z] = %f\n",
		matrix.row_3.coord[X], matrix.row_3.coord[Y], matrix.row_3.coord[Z]);
	printf("row_4[x] = %f    row_4[y] = %f    row_4[z] = %f\n",
		matrix.row_4.coord[X], matrix.row_4.coord[Y], matrix.row_4.coord[Z]);
}
