#ifndef MINI_RT_STRUCT_H
#define MINI_RT_STRUCT_H

/*


typedef struct s_sphere
{
	int				type;
	struct s_coord	*coord;
	float			diameter;
	struct s_rgb	*rgb;
	struct s_sphere	*next;
}	t_sphere;

typedef struct s_plan
{
	int 			type;
	struct s_coord	*coord;
	struct s_vec3	*vertex;
	struct s_rgb	*rgb;
	struct s_plan	*next;
}	t_plan;

typedef struct s_cylinder
{
	int 				type;
	struct s_coord		*coord;
	struct s_vec3		*vertex;
	float				diameter;
	float				height;
	struct s_rgb		*rgb;
	struct s_cylinder	*next;
}	t_cylinder;

typedef struct s_obj
{
	int 			type;
	t_ambient_light *ambient_light;
	t_camera		*camera;
	t_diffuse_light	*diffuse_light;
	t_plan			*plan;
	t_sphere 		*sphere;
	t_cylinder 		*cylinder;
}		t_obj;
 */

typedef struct s_coord
{
	double	x;
	double	y;
	double	z;
}	t_coord;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_ambient_light
{
	int 					type;
	double					intensity;
	struct s_rgb			rgb[1];
}	t_ambient_light;

typedef struct s_camera
{
	int 				type;
	struct s_coord		coord[1];
	struct s_vec3		vertex[1];
	int 				fov;
}	t_camera;

typedef struct s_diffuse_light
{
	int 					type;
	struct s_coord			coord[1];
	double					intensity;
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
	struct s_coord	coord[1];
	struct s_vec3	vertex[1];
	struct s_rgb	rgb[1];
	double			diameter;
	double			height;
	struct s_obj	*next;
}	t_obj;

typedef struct s_mlx
{
	void		*ptr;
	void		*window;
	void		*image;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
}				t_mlx;

typedef struct s_parsing
{
	char	**input_list;
	char 	**obj_info;
	t_obj	*objs;
	t_scene scene[1];
	_Bool 	camera;
	_Bool	ambient_light;
	_Bool 	diffuse_light;
}	t_parsing;

#endif
