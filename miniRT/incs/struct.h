#ifndef MINI_RT_STRUCT_H
#define MINI_RT_STRUCT_H

typedef struct s_ambient_light
{
	int 					type;
	float 					intensity;
	struct s_rgb			*rgb;
}	t_ambient_light;

typedef struct s_camera
{
	int 				type;
	struct s_coord		*coord;
	struct s_vector3	*vertex;
	int 				fov;
}	t_camera;

typedef struct s_diffuse_light
{
	int 					type;
	struct s_coord			*coord;
	float 					intensity;
}	t_diffuse_light;

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
	int 				type;
	struct s_coord		*coord;
	struct s_vector3	*vertex;
	struct s_rgb		*rgb;
	struct s_plan		*next;
}	t_plan;

typedef struct s_cylinder
{
	int 				type;
	struct s_coord		*coord;
	struct s_vector3	*vertex;
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

typedef struct s_coord
{
	float	x;
	float	y;
	float	z;
}	t_coord;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

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
}	t_parsing;

#endif
