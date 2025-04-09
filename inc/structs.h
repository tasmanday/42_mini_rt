/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:03:07 by tday              #+#    #+#             */
/*   Updated: 2025/02/01 19:04:54 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef STRUCTS_H
#define STRUCTS_H

typedef enum s_Error
{
	INVALID_FLOAT = 0,
	INVALID_INT = 1,
	INVALID_INPUT_VALUE = 2,
	MISSING_OR_EXTRA_INPUT_VALUES = 3,
	COLOUR_VALUES_OUTSIDE_OF_RANGE = 4,
	AMBIENT_LIGHT_OUTSIDE_OF_RANGE = 5,
	LIGHT_BRIGHTNESS_RATIO_OUTSIDE_OF_RANGE = 6,
	CAMERA_FOV_OUTSIDE_OF_RANGE = 7,
	AMBIENT_LIGHT_ERROR = 10,
	CAMERA_ERROR = 11,
	LIGHT_ERROR = 12,
	SPHERE_ERROR = 13,
	PLANE_ERROR = 14,
	CYLINDER_ERROR = 15,
}	t_Error;

typedef struct s_Vector3
{
	float		x;
	float		y;
	float		z;
}	t_Vector3;

typedef struct s_Colour4
{
	float		r;
	float		g;
	float		b;
	float		a;
}				t_Colour4;

typedef struct s_AmbientLight
{
	float		ratio;
	t_Colour4	colour;
}	t_AmbientLight;

typedef struct s_Camera
{
	t_Vector3	position;
	t_Vector3	orientation;
	int			fov;
}	t_Camera;

typedef struct s_Light
{
	t_Vector3	position;
	float		brightness;
	t_Colour4	colour;
}	t_Light;

typedef struct s_Sphere
{
	t_Vector3	center;
	float		diameter;
	t_Colour4	colour;
}	t_Sphere;

typedef struct s_Plane
{
	t_Vector3	point;
	t_Vector3	normal;
	t_Colour4	colour;
}	t_Plane;

typedef struct s_Cylinder
{
	t_Vector3	center;
	t_Vector3	axis;
	float		diameter;
	float		height;
	t_Colour4	colour;
}	t_Cylinder;

typedef enum s_ObjectType
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_ObjectType;

typedef struct Object
{
	t_ObjectType	type;
	union
	{
		t_Sphere	sphere;
		t_Plane		plane;
		t_Cylinder	cylinder;
	}	u_data;
	struct Object	*next;
}	t_Object;

typedef struct s_Mlx
{
	int			width;
	int			height;
	int			**z_matrix;
	int			zoom;
	int			colour;
	int			amplify;
	int			shift_x;
	int			shift_y;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*img_data;
	int			bpp;
	int			size_line;
	int			endian;
}				t_Mlx;

typedef struct s_ray
{
	t_Vector3	ray_origin;
	t_Vector3	ray_dir;
	bool		intersects_object;
	float		closest_hit_distance;
	int			cyl_closest_point;
	t_Object	*closest_object;
	t_Colour4	colour;
	t_Vector3	normal_at_intersection;
	t_Vector3	intersection_point;
}				t_ray;

typedef struct s_pixel
{
	t_ray			*TL;
	t_ray			*TR;
	t_ray			*BL;
	t_ray			*BR;
	unsigned int	avg_colour;
}				t_pixel;

typedef	struct s_mem
{
	t_pixel			**pixels;
	t_ray			**corner_ray;
}				t_mem;

typedef struct s_Scene
{
	t_AmbientLight	ambient_light;
	t_Camera		camera;
	t_Light			light;
	int				ambient_light_parsed;
	int				camera_parsed;
	int				light_parsed;
	struct Object	*objects;
	int				object_count;
	t_Mlx			mlx;
	t_mem			*mem;
}	t_Scene;

#endif