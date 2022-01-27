#ifndef STRUCT_H
# define STRUCT_H

#include "lib_math.h"

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
	double	closest_hit;
}	t_ray;

typedef struct s_hit
{
	double	dist;
	t_vec3	intersection;
	t_vec3	normal;
	t_rgb	color;
}	t_hit;

typedef struct s_ambient_light
{
	int				type;
	double			intensity;
	struct s_rgb	color[1];
}	t_ambient_light;

typedef struct s_camera
{
	int			type;
	t_vec3		origin[1];
	t_vec3		dir[1];
	double		fov;
}	t_camera;

typedef struct s_diffuse_light
{
	int				type;
	t_vec3			coord[1];
	double			intensity;
}	t_diffuse_light;

typedef struct s_scene
{
	struct s_camera			camera[1];
	struct s_diffuse_light	diffuse_light[1];
	struct s_ambient_light	ambient_light[1];
}	t_scene;

typedef struct s_obj
{
	int				type;
	t_vec3			origin[1];
	t_vec3			dir[1];
	t_rgb			color[1];
	double			diameter;
	double			height;
	struct s_obj	*next;
}	t_obj;

typedef struct s_image
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_image;

typedef struct s_mlx
{
	void		*ptr;
	void		*window;
	t_image		*image;
}				t_mlx;

typedef struct s_parsing
{
	char	**input_list;
	char	**obj_info;
	t_obj	*objs;
	t_scene	scene[1];
	_Bool	camera;
	_Bool	ambient_light;
	_Bool	diffuse_light;
}	t_parsing;

typedef struct s_data
{
	t_mlx		*mlx;
	t_scene		*scene;
	t_obj		*obj;
	int			pixel_x;
	int			pixel_y;
	t_matrix4	cam_to_world_matrix;
}	t_data;

typedef _Bool	t_op(t_ray *ray, t_obj *obj, t_hit *hit);

#endif
