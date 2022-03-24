/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:49:37 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/24 10:49:39 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <math.h>

# define HEIGHT 480
# define WIDTH 720

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
void			fill_ambient_light(t_parsing *parsing,
					t_ambient_light *ambient_light, char *line);
void			fill_camera(t_parsing *parsing, t_camera *camera, char *line);
void			fill_diffuse_light(t_parsing *parsing, char *line);
void			fill_scene(int type, t_parsing *var, char *line);
t_obj			*list_to_tab(t_obj *obj, t_parsing *parsing_var);
t_obj			*new_obj(
					int type, double diameter, double height, t_parsing *var);
void			fill_obj(int type, t_parsing *var, char *line);
void			obj_add_back(t_obj **obj_list, t_obj *to_add);
_Bool			is_valid_extension(char *arg);
_Bool			file_is_complete(t_parsing *var, char *file);
int				check(void *obj, int type);
int				parsing(char **argv, int argc, t_parsing *parsing_var);
int				is_valid_type(char *type);
int				list_len(t_obj *obj);
int				load_file(char **argv, int argc, int *fd);
int				convert_file_to_string(int fd, char **input);
int				cylinder_check(t_obj *cylinder);
int				plane_check(t_obj *plane);
int				sphere_check(t_obj *sphere);
int				diffuse_light_check(t_diffuse_light *diffuse_light);
int				camera_check(t_camera *camera);
int				ambient_light_check(t_ambient_light *ambient_light);
void			ft_free(void *to_free);
void			free_str_tab(char **tab);
void			free_list(t_obj *obj);
void			free_list_error(t_obj *obj);
void			clean_parsing_var(t_parsing *parsing_var);
void			free_tab(void **tab, int size);
int				sphere_format_error(char *str);
int				plane_format_error(char *str);
int				cylinder_format_error(char *str);
int				is_valid_vertex(t_vec3 *vertex);
int				is_in_range(double min, double max, double value);
int				is_valid_rgb(t_vec3 *rgb);
int				ambient_light_format_error(char *str);
int				camera_format_error(char *str);
int				diffuse_light_format_error(char *str);
int				extension_error(char *str);
int				arg_nb_error(void);
int				is_dir_error(char *str);
int				file_error(char *str);
int				incomplete_file_error(char *str);
int				strjoin_error(void);
int				read_error(char *str);
int				close_error(char *str);
void			error_coordinates(void);
void			error_diameter(void);
void			error_rgb(void);
void			error_height(void);
void			error_vertex(void);
void			error_intensity(void);
void			file_format_error(void);
int				invalid_type_error(char *str);

/********************************** CAMERA ************************************/

t_matrix4		built_cam_to_world_matrix(t_camera *camera);
void			update_camera_ray(t_ray *cam_ray,
					t_data *data);
void			init_camera_ray(t_ray *cam_ray, t_data *data);
void			init_euler_angles(t_camera *camera);
void			check_limit_angle(double *angle);

/******************************** RAYTRACING **********************************/

void			run_minirt(t_data *data);
void			run_raytracing(t_mlx *mlx, t_data *data);
void			init_var_hit(_Bool *hit_obj, t_ray *hit, t_vec3 *color);
void			init_hit(t_ray *hit);
double			compute_shadow(
					t_obj *obj, t_ray *ray, t_diffuse_light *light);
t_vec3			get_color_pixel(t_obj *obj, t_data *data,
					t_ray *ray, int rebound);

/******************************** OBJECTS *************************************/

_Bool			hit_sphere(t_ray *ray, t_obj *obj, t_ray *hit);
_Bool			hit_plane(t_ray *ray, t_obj *obj, t_ray *hit);
_Bool			hit_cylinder(t_ray *ray, t_obj *obj, t_ray *hit);
void			check_direction_normal(t_ray *ray, t_ray *hit);
t_vec3			get_hit_point(t_ray ray);
void			copy_ray(t_ray *dest, t_ray src);

/********************************* LIGHTING ***********************************/

t_vec3			get_light(t_data *data, t_ray hit);
t_vec3			get_ambient_light(t_scene *scene);
void			draw_pixel(t_image *image, unsigned long color, t_data *data);
unsigned long	create_rgb_struct(t_vec3 *color);
void			clamp_intensity(double *intensity);
void			clamp_color(int *color);

#endif
