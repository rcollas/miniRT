#include "miniRT.h"

int	fill_rgb(char *rgb_values, t_vec3 *rgb)
{
	char	**split_rgb;
	int 	i;

	i = 0;
	split_rgb = ft_split(rgb_values, ",");
	while (split_rgb[i])
		i++;
	if (i != 3)
		return (FAIL);
	rgb->coord[R] = ft_atoi(split_rgb[0]);
	rgb->coord[G] = ft_atoi(split_rgb[1]);
	rgb->coord[B] = ft_atoi(split_rgb[2]);
	free_str_tab(split_rgb);
	return (SUCCESS);
}

int	fill_coordinates(char *coordinates_values, t_vec3 *coordinates)
{
	char **split_coordinates;
	int i;

	i = 0;
	split_coordinates = ft_split(coordinates_values, ",");
	while (split_coordinates[i])
		i++;
	if (i != 3)
		return (FAIL);
	coordinates->coord[X] = ft_atof(split_coordinates[0]);
	coordinates->coord[Y] = ft_atof(split_coordinates[1]);
	coordinates->coord[Z] = ft_atof(split_coordinates[2]);
	free_str_tab(split_coordinates);
	return (SUCCESS);
}

int	fill_vertex(char *vertex_values, t_vec3 *vertex)
{
	char	**split_vertex;
	int 	i;

	i = 0;
	split_vertex = ft_split(vertex_values, ",");
	while (split_vertex[i])
		i++;
	if (i != 3)
		return (FAIL);
	vertex->coord[X] = ft_atof(split_vertex[0]);
	vertex->coord[Y] = ft_atof(split_vertex[1]);
	vertex->coord[Z] = ft_atof(split_vertex[2]);
	free_str_tab(split_vertex);
	return (SUCCESS);
}
