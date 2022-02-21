#ifndef STRUCT_H
# define STRUCT_H

# include "lib_math.h"

struct			s_obj;

typedef struct s_ray
{
	t_vec3			origin;
	t_vec3			dir;
	double			dist;
	t_vec3			color;
	double			pixel_shadow;
	double			shine_factor;
	struct s_obj	*obj_ref;
}	t_ray;

typedef struct s_ambient_light
{
	int			type;
	double		intensity;
	t_vec3		color[1];
}	t_ambient_light;

typedef struct s_camera
{
	int			type;
	t_vec3		origin[1];
	t_vec3		dir[1];
	double		fov;
	t_vec3		forward;
	t_vec3		up;
	t_vec3		right;
	double		yaw_angle;
	double		pitch_angle;
}	t_camera;

typedef struct s_diffuse_light
{
	int			type;
	t_vec3		coord[1];
	double		intensity;
	t_vec3		color[1];
}	t_diffuse_light;

typedef struct s_scene
{
	t_camera		camera[1];
	t_diffuse_light	diffuse_light[1];
	t_ambient_light	ambient_light[1];
}	t_scene;

typedef _Bool	t_op(t_ray *ray, struct s_obj *obj, t_ray *hit);

typedef struct s_obj
{
	int				type;
	t_vec3			origin[1];
	t_vec3			dir[1];
	t_vec3			color[1];
	double			diameter;
	double			height;
	t_op			*hit_object;
	double			shine_factor;
	struct s_obj	*next;
}	t_obj;

typedef struct s_image
{
	void		*img_ptr;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_image;

typedef struct s_mlx
{
	void		*ptr;
	void		*window;
	t_image		*image;
}				t_mlx;

typedef struct s_parsing
{
	char		**input_list;
	char		**obj_info;
	t_obj		*objs;
	t_scene		scene[1];
	_Bool		camera;
	_Bool		ambient_light;
	_Bool		diffuse_light;
}	t_parsing;

typedef struct s_data
{
	t_mlx		*mlx;
	t_scene		*scene;
	t_obj		*obj;
	int			pixel_x;
	int			pixel_y;
	t_matrix4	cam_to_world_matrix;
	int			lighting;
}	t_data;

#endif
