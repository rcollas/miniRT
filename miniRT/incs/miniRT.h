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
# include "libft.h"
# include "lib_math.h"
# include "struct.h"
# include "error.h"
# include "enum.h"
# include "utils.h"
# ifdef __linux__
# include "mlx_int.h"
#  define IS_LINUX 1
# else
#  define IS_LINUX 0
# endif

# define HEIGHT 480
# define WIDTH 720

/*********************************************** MLX_SETUP *********************************************************/

t_mlx		*setup_mlx(void);
void		events_loop(t_data *data);
void		clean_data(t_data *data);
void		clean_mlx(t_mlx *mlx);
void		free_list(t_obj *obj);
int			check(void *obj, int type);
void		init_data(t_parsing *parsing_var, t_data *data);
void 		init_image(t_mlx *mlx, t_data *data);

/************************************************ PARSING **********************************************************/

void		fill_structure(t_parsing *parsing_var);
int			fill_rgb(char *rgb_values, t_vec3 *rgb);
int			fill_coordinates(char *coordinates_values, t_vec3 *coordinates);
int			fill_vertex(char *vertex_values, t_vec3 *vertex);
void		fill_ambient_light(t_parsing *parsing, t_ambient_light *ambient_light, char *line);
void		fill_camera(t_parsing *parsing, t_camera *camera, char *line);
void		fill_diffuse_light(t_parsing *parsing, t_diffuse_light *diffuse_light, char *line);
void		fill_scene(int type, t_parsing *var, char *line);
t_obj		*new_obj(int type, double diameter, double height);
void		fill_obj(int type, t_parsing *var, char *line);
void		obj_add_back(t_obj **obj_list, t_obj *to_add);
_Bool		is_valid_extension(char *arg);
int			check(void *obj, int type);
void		print_list(t_obj *obj);
int			parsing(char **argv, int argc, t_parsing *parsing_var);
int			is_valid_type(char *type);
void		ft_free(void *to_free);

/*********************************************** RAYTRACING ********************************************************/

void		run_raytracing(t_mlx *mlx, t_scene *scene, t_data *data);
_Bool		hit_sphere(t_ray *ray, t_obj *obj, t_hit *hit);
_Bool		hit_plane(t_ray *ray, t_obj *obj, t_hit *hit);
_Bool		hit_cylinder(t_ray *ray, t_obj *obj, t_hit *hit);
_Bool		hit_disk(t_ray *ray, t_obj *obj, t_hit *hit);

/************************************************* CAMERA **********************************************************/

t_matrix4	built_cam_to_word_matrix(t_camera *camera);
void		update_camera_ray(t_ray *cam_ray, t_data *data);
void		init_camera_ray(t_ray *cam_ray, t_data *data);

/************************************************** COLOR **********************************************************/

void		get_color_pixel(t_scene *scene, t_hit hit, t_ray ray, int *color);
void		draw_pixel(t_image *image, int color, t_data *data);
int			create_trgb_struct(int transparency, t_vec3 *color);
int			create_trgb(int transparency, int red, int green, int blue);
void		check_limit_color(t_vec3 *color);
void		clamp_intensity(double *intensity);
void		clamp_color(int *color);
t_vec3		init_color(double red, double green, double blue);
void		copy_rgb(t_vec3 *dest, t_vec3 src);
t_vec3		mul_rgb_and_const(t_vec3 color, double k);
t_vec3		mul_rgb(t_vec3 color_1, t_vec3 color_2);
t_vec3		add_rgb(t_vec3 color_1, t_vec3 color_2);

#endif
