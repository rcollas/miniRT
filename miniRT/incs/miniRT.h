#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <math.h>
# include <pthread.h> // only for BONUS

# define BONUS 1
# define HEIGHT 480
# define WIDTH 720
# define THREADS 8
# define PASSES 3
# define REBOUND 8

# include "mlx.h"
# include "libft.h"
# include "lib_math.h"
# include "struct.h"
# include "error.h"
# include "enum.h"
# include "utils.h"
# ifdef __linux__
#  include "mlx_int.h"
#  define IS_LINUX 1
# else
#  define IS_LINUX 0
# endif

/******************************** MLX_SETUP ***********************************/

t_mlx			*setup_mlx(t_parsing *var);
void			events_loop(t_data *data);
void			clean_data(t_data *data);
void			clean_mlx(t_mlx *mlx);
int				check(void *obj, int type);
void			init_data(t_parsing *parsing_var, t_data *data);
void			init_image(t_mlx *mlx, t_data *data);

/********************************* PARSING ************************************/

void			fill_structure(t_parsing *parsing_var);
int				fill_rgb(char *rgb_values, t_vec3 *rgb);
int				fill_coordinates(char *coordinates_values, t_vec3 *coordinates);
int				fill_vertex(char *vertex_values, t_vec3 *vertex);
void			fill_sky(t_parsing *var, char *line);
void			fill_disk(t_parsing *var, char *line);
void			fill_cone(t_parsing *var, char *line);
void			fill_square(t_parsing *var, char *line);
void			fill_ambient_light(t_parsing *parsing,
					t_ambient_light *ambient_light, char *line);
void			fill_camera(t_parsing *parsing, t_camera *camera, char *line);
void			fill_diffuse_light(t_parsing *parsing,
					t_diffuse_light *diffuse_light, char *line);
void			fill_scene(int type, t_parsing *var, char *line);
t_obj			*new_obj(
					int type, double diameter, double height, t_parsing *var);
void			fill_obj(int type, t_parsing *var, char *line);
void			obj_add_back(t_obj **obj_list, t_obj *to_add);
_Bool			is_valid_extension(char *arg);
int				check(void *obj, int type);
int				parsing(char **argv, int argc, t_parsing *parsing_var);
int				is_valid_type(char *type);
void			ft_free(void *to_free);
void			free_str_tab(char **tab);
void			free_list(t_obj *obj);
void			clean_parsing_var(t_parsing *parsing_var);
void			free_tab(void **tab, int size);

/********************************** CAMERA ************************************/

t_matrix4		built_cam_to_world_matrix(t_camera *camera);
void			update_camera_ray(t_ray *cam_ray,
					t_data *data, t_thread *thread);
void			init_camera_ray(t_ray *cam_ray, t_data *data);
void			init_euler_angles(t_camera *camera);
void			check_limit_angle(double *angle);

/******************************** RAYTRACING **********************************/

void			run_minirt(t_data *data);
void			run_raytracing(t_mlx *mlx, t_data *data, t_thread *thread);
void			run_multithreading(t_data *data);
void			init_var_hit(_Bool *hit_obj, t_ray *hit, t_vec3 *color);
void			run_path_tracing(t_ray *cam_ray, unsigned long *color,
					t_data *data, t_thread *thread);
double			compute_shadow(
					t_obj *obj, t_ray *ray, t_diffuse_light *light);
t_vec3			get_color_pixel(t_obj *obj, t_data *data,
					t_ray *ray, int rebound);

/******************************** OBJECTS *************************************/

_Bool			hit_sphere(t_ray *ray, t_obj *obj, t_ray *hit);
_Bool			hit_plane(t_ray *ray, t_obj *obj, t_ray *hit);
_Bool			hit_cylinder(t_ray *ray, t_obj *obj, t_ray *hit);
_Bool			hit_disk(t_ray *ray, t_obj *obj, t_ray *hit);
_Bool			hit_square(t_ray *ray, t_obj *obj, t_ray *hit);
void			check_direction_normal(t_ray *ray, t_obj *obj, t_ray *hit);
t_vec3			get_hit_point(t_ray ray);
void			copy_ray(t_ray *dest, t_ray src);
_Bool			hit_hyperboloid(t_ray *ray, t_obj *obj, t_ray *hit);
_Bool			hit_cone(t_ray *ray, t_obj *obj, t_ray *hit);
_Bool			check_cone_height(t_ray *ray, t_obj *obj, double ray_dist);
void			compute_normal_cone(t_ray *ray, t_obj *obj, t_ray *hit);

/********************************* LIGHTING ***********************************/

t_vec3			get_light(t_data *data, t_ray hit, t_ray ray);
t_vec3			sum_phong_lights(
					t_scene *scene, t_ray hit, t_ray ray, t_data *data);
t_vec3			get_ambient_light(t_scene *scene);
void			draw_pixel(t_image *image, unsigned long color,
					t_thread *thread);
unsigned long	create_rgb_struct(t_vec3 *color);
unsigned long	create_rgb(int red, int green, int blue);
unsigned long	create_trgb_struct(int transparency, t_vec3 *color);
unsigned long	create_trgb(int transparency, int red, int green, int blue);
void			check_limit_color(t_vec3 *color);
void			clamp_intensity(double *intensity);
void			clamp_color(int *color);

/********************************** TEXTURE ***********************************/

int				parse_param_texture(
					t_parsing *var, t_obj *obj, int i, int nb_ref);
_Bool			check_error_param_texture(int i, int nb_ref);
int				parse_checker(t_obj *obj, char *rgb);
void			parse_texture(t_parsing *var, t_obj *obj, char *filename);
void			parse_bump_map(t_parsing *var, t_obj *obj, char *filename);
_Bool			check_file_texture(char *filename);
void			open_texture(t_image *texture, char *file, t_parsing *var);
void			create_texture(t_ray *hit, t_image *texture, t_vec3 *color);
void			create_checker(t_ray *hit);
void			handle_texture(t_ray *hit);
void			get_sphere_uv(t_ray hit, t_vec2 *uv);
void			get_cylinder_uv(t_ray hit, t_vec2 *uv);
void			get_plane_uv(t_ray hit, t_vec2 *uv);
void			get_disk_uv(t_ray hit, t_vec2 *uv);
void			get_square_uv(t_ray hit, t_vec2 *uv);
void			apply_bump_map(t_ray *hit);
t_vec2			transform_point_in_obj_space(t_vec3 hit_point,
					t_vec3 obj_origin, double max_dimension, t_vec3 obj_dir);

/***************************** OPTIMIZATION UTILS *****************************/

# include <sys/time.h>

double			get_timestamp(double start);
double			get_time(void);
double			elapsed_time(double start, double end);

#endif
