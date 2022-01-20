#ifndef MINI_RT_STRUCT_H
#define MINI_RT_STRUCT_H

typedef struct s_ambient_light
{
	int 			type;
	float 			intensity;
	struct s_rgb	*rgb;
}	t_ambient_light;

typedef struct s_diffuse_light
{
	int 			type;
	struct s_coord	*coord;
	float 			intensity;
	struct s_rgb	*rgb;
}	t_diffuse_light;

typedef struct s_camera
{
	int 				type;
	struct s_coord		*coord;
	struct s_vertex		*vertex;
	int 				fov;
}	t_camera;

typedef struct s_obj
{
	int 			type;
	struct t_coord	*coord;
	struct t_rgb	*rgb;
	//pointer to t_sphere
	//pointer to next obj
}		t_obj;

typedef struct s_coord
{
	float	x;
	float	y;
	float	z;
}	t_coord;

typedef struct s_vertex
{
	float	x;
	float	y;
	float	z;
}	t_vertex;

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

#endif
