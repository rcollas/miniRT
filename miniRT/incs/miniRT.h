#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "mlx.h"
# ifdef __linux__
# include "mlx_int.h"
# endif
# include "libft.h"
# include "error.h"
# include "enum.h"
# include "struct.h"
# include "utils.h"

t_mlx	*setup_mlx(void);
void	events_loop(t_mlx *mlx);
void	clean_mlx(t_mlx *mlx);
int		parsing(char **argv, int argc, t_parsing *parsing_var);
int		is_valid_type(char *type);
void	ft_free(void *to_free);
void	free_list(t_obj *obj);
int		check(void *obj, int type);

int		fill_rgb(char *rgb_values, t_rgb *rgb);
int		fill_coordinates(char *coordinates_values, t_coord *coordinates);
int		fill_vertex(char *vertex_values, t_vec3 *vertex);
void	fill_ambient_light(t_parsing *parsing, t_ambient_light *ambient_light, char *line);
void	fill_camera(t_parsing *parsing, t_camera *camera, char *line);
void	fill_diffuse_light(t_parsing *parsing, t_diffuse_light *diffuse_light, char *line);
/*
void	fill_sphere(t_parsing *parsing, t_sphere *sphere, char *line);
void	fill_plan(t_parsing *parsing, t_plan *plan, char *line);
void	fill_cylinder(t_parsing *parsing, t_cylinder *cylinder, char *line);
void	fill_by_type(int type, t_parsing *var, char *line);
 */
void	fill_structure(t_parsing *parsing_var);
t_obj	*new_obj(int type, double diameter, double height);
void	fill_scene(int type, t_parsing *var, char *line);
void	fill_obj(int type, t_parsing *var, char *line);
void	obj_add_back(t_obj **obj_list, t_obj *to_add);
void	print_list(t_obj *obj);
_Bool	is_valid_extension(char *arg);

#endif
