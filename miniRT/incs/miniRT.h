#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <math.h>
# include "mlx.h"
# ifdef __linux__
# include "mlx_int.h"
# endif
# include "libft.h"
# include "error.h"
# include "enum.h"
# include "struct.h"
# include "utils.h"
# include "lib_vector.h"

# define HEIGHT 480
# define WIDTH 720

/*********************************************** MLX_SETUP *********************************************************/

t_mlx	*setup_mlx(void);
void	events_loop(t_data *data);
void	clean_data(t_data *data);
void	clean_mlx(t_mlx *mlx);
void	free_list(t_obj *obj);
int		check(void *obj, int type);
void	init_data(t_parsing *parsing_var, t_data *data);
void 	init_image(t_mlx *mlx, t_data *data);

/************************************************ PARSING **********************************************************/

void	fill_structure(t_parsing *parsing_var);
int		fill_rgb(char *rgb_values, t_rgb *rgb);
int		fill_coordinates(char *coordinates_values, t_coord *coordinates);
int		fill_vertex(char *vertex_values, t_vec3 *vertex);
void	fill_ambient_light(t_parsing *parsing, t_ambient_light *ambient_light, char *line);
void	fill_camera(t_parsing *parsing, t_camera *camera, char *line);
void	fill_diffuse_light(t_parsing *parsing, t_diffuse_light *diffuse_light, char *line);
void	fill_scene(int type, t_parsing *var, char *line);
t_obj	*new_obj(int type, double diameter, double height);
void	fill_obj(int type, t_parsing *var, char *line);
void	obj_add_back(t_obj **obj_list, t_obj *to_add);
_Bool	is_valid_extension(char *arg);
int		check(void *obj, int type);
void	print_list(t_obj *obj);
int		parsing(char **argv, int argc, t_parsing *parsing_var);
int		is_valid_type(char *type);
void	ft_free(void *to_free);

#endif
