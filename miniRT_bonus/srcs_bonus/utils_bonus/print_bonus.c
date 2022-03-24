#include "miniRT_bonus.h"

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

void	print_matrix4(t_matrix4 matrix)
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

void	print_matrix3(t_matrix3 matrix)
{
	printf("row_1[x] = %f    row_1[y] = %f    row_1[z] = %f\n",
		matrix.row_1.coord[X], matrix.row_1.coord[Y], matrix.row_1.coord[Z]);
	printf("row_2[x] = %f    row_2[y] = %f    row_2[z] = %f\n",
		matrix.row_2.coord[X], matrix.row_2.coord[Y], matrix.row_2.coord[Z]);
	printf("row_3[x] = %f    row_3[y] = %f    row_3[z] = %f\n\n\n",
		matrix.row_3.coord[X], matrix.row_3.coord[Y], matrix.row_3.coord[Z]);
}
