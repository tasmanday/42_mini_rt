/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:11:49 by atang             #+#    #+#             */
/*   Updated: 2025/01/06 17:27:09 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/inc/libft.h"
# include <unistd.h> // read, close
# include <stdio.h> // size_t, printf
# include <stdlib.h>
# include <fcntl.h> // O_RDONLY macro
# include <string.h>
# include <sys/types.h> // for ssize_t
# include <math.h>
# include <errno.h>
# include "../minilibx/mlx.h"

// DEFINITIONS //

# define BUFFER_SIZE 1024 
# define MAX_OBJECTS 100
# define MAX_TOKEN_LENGTH 50
# define SUCCESS 0
# define FAILURE -99

# define RST    "\033[0m"      /* Reset to default color */
# define RED	"\033[1;31m"   /* Bold Red */
# define G      "\033[1;32m"   /* Bold Green */
# define Y      "\033[1;33m"   /* Bold Yellow */
# define B      "\033[1;34m"   /* Bold Blue */
# define M      "\033[1;35m"   /* Bold Magenta */
# define C      "\033[1;36m"   /* Bold Cyan */
# define W      "\033[1;37m"   /* Bold White */
# define U      "\033[4m"      /* Underlined */

// STRUCTURES//

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

typedef struct s_Colour
{
	int			r;
	int			g;
	int			b;
}	t_Colour;

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
}				t_ray;

typedef struct s_pixel
{
	t_ray			*TL;
	t_ray			*TR;
	t_ray			*BL;
	t_ray			*BR;
	t_ray			mid;
	unsigned int	avg_colour;
}				t_pixel;

typedef	struct s_mem
{
	t_pixel		**pixels;
	t_ray		**corners;
}				t_mem;

typedef struct s_QuadraticCoefficients
{
	float		a;
	float		b;
	float		c;
}				t_Quad;

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
}	t_Scene;

// PROTOTYPES //

// error.c //
int			err_return(const char *message);
int			err_exit(t_Error error);
void		warn_err_exit(const char *message, t_Error error);
int			err_free_exit(t_Error error, struct Object *current, t_Scene *scene);
int			warn_err_free_exit(const char *message, t_Error error, struct Object *current, t_Scene *scene);

// file_check.c //
int			file_exists(char *filename);
int			file_status(const char *filename);
int			filename_error(char	*filename);

/*/ get_next_line_utils.c //
size_t		gnl_strlen(const char *str);
char		*gnl_strchr(char *str, int target_char);
char		*gnl_strjoin(char *first_str, char *second_str);
char		*gnl_initialise_str(void);

// get_next_line.c //
char		*read_and_append_lines(int fd, char	*stash);
char		*extract_line_from_stash(char	*stash);
char		*remaining_stash_after_extraction(char *stash);
char		*get_next_line(int fd, char **line); */

// mlx.c //
void		initialise_data(t_Scene	*mlx);
int			deal_key(int key, t_Scene *scene);
int			close_button_hook(t_Scene *scene);
void		handle_exit(t_Scene *scene);

// object_utils.c //
const char	*get_object_type_str(int type);
void		print_objects_in_scene(struct Object *objects);
int			add_object(t_Scene *scene, struct Object *new_object);
void		free_objects(t_Scene *scene);

// parse_elements.c //
int			parse_ambient_light(char **line, t_AmbientLight *ambient_light); // For line
int			parse_camera(char **line, t_Camera *camera);
int			parse_light(char **line, t_Light *light);
int			parse_position(t_Vector3 *position, char **token);
int			parse_orientation(t_Vector3 *orientation, char **token);

// parse_main.c //
int			process_line(char *line, t_Scene *scene);
int			parse_rt_file(const char *filename, t_Scene *scene);
int			parse_line(char	*line, t_Scene *scene);

// parse_objects.c //
int			parse_sphere(char **line, t_Scene *scene);
int			parse_plane(char **line, t_Scene *scene);
int			parse_cylinder(char **line, t_Scene *scene);

// parse_utils.c //
int			parse_rgb(t_Colour4 *colour, char **line);
int 		parse_vector3(char **line, t_Vector3 *vec);
int			parse_position(t_Vector3 *position, char **line);
int			parse_orientation(t_Vector3 *orientation, char **line);
// --> OG below
//int			parse_vector3_OG(t_Vector3 *vec); //OG
//int			parse_rgb_OG(t_Colour *colour, char **token); //OG
//int			parse_position_OG(t_Vector3 *position, char **token); //OG
//int			parse_orientation_OG(t_Vector3 *orientation, char **token); //OG

// print_elements.c //
void		print_ambient_light(t_AmbientLight *ambient);
void		print_camera(const t_Camera *camera);
void		print_light(const t_Light *light);

// print_objects.c //
void		print_sphere(const struct Object *object);
void		print_plane(const struct Object *object);
void		print_cylinder(const struct Object *object);
void		print_all_objects(const t_Scene *scene);

// print_utils.c //
int			print_error_and_return(const char *message, const char *token);

// utils.c //
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			get_next_token(char **line, char **token);
char		*ft_strtok(char **line, const char *delim);
float		parse_float(char **str);
int			parse_int(char	**str);

// miscellaneous //

// organise later //
int			resize_window_hook(int width, int height, t_Scene *scene, t_mem *mem);
int			expose_hook(t_Scene *scene);
t_Vector3	vector(float x, float y, float z);
t_Vector3	vect_normalise(t_Vector3 v);
t_Vector3	vect_add(t_Vector3 a, t_Vector3 b);
t_Vector3	vect_subtract(t_Vector3 a, t_Vector3 b);
t_Vector3	vect_cross(t_Vector3 a, t_Vector3 b);
float		vect_dot(t_Vector3 a, t_Vector3 b);
t_Vector3	vect_multiply_scalar(t_Vector3 v, float scalar);
float		vect_distance(t_Vector3 a, t_Vector3 b);

//void		compute_ray_directions(t_Scene *scene);
void		init_ray(t_Scene *scene, t_ray *ray, int x, int y);
t_Vector3	get_ray_direction(t_Scene *scene, int x, int y);
t_Vector3	apply_camera_orientation(t_Vector3 ray, t_Scene *scene);
bool		camera_pointed_straight_up_or_down(t_Vector3 orientation);

bool		ray_intersects_sphere(t_ray *ray, t_Sphere sphere, \
			float *distance);
bool		ray_intersects_cylinder(t_ray *ray, t_Cylinder cylinder, \
			float *distance);
/* bool		ray_intersects_cylinder(t_Scene *scene, t_Vector3 ray_dir, \
			float *distance); */
bool		ray_intersects_plane(t_ray *ray, t_Vector3	point_on_plane, \
			t_Vector3	plane_norm_vect, float *distance);

void		put_pixels_to_image(t_mem *mem, t_Scene *scene);
t_pixel		**allocate_pixel_array(int width, int height);
t_ray		**allocate_corner_array(int width, int height);
void		init_mem(t_mem *mem, t_Scene *scene);
void		init_pixel_array(t_mem *mem, t_Scene *scene);
void		check_object_intersection(t_Scene *scene, t_ray *ray);
void		check_corner_intersections(t_mem *mem, t_Scene *scene);
void		check_mid_intersections(t_mem *mem, t_Scene *scene);
void		average_pixel_colours(t_mem *mem, t_Scene *scene);
void		trace_rays(t_mem *mem, t_Scene *scene);
void		free_everything(t_mem *mem, t_Scene *scene);

#endif
