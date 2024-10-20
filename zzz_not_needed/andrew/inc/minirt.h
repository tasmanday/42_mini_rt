/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:11:49 by atang             #+#    #+#             */
/*   Updated: 2024/10/20 13:51:20 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h> // read, close
# include <stdio.h> // size_t, printf
# include <stdlib.h>
# include <fcntl.h> // O_RDONLY macro
# include <string.h>
# include <sys/types.h> // for ssize_t
# include "../minilibx/mlx.h"

// DEFINITIONS //

# define BUFFER_SIZE 1024 
# define MAX_OBJECTS 100
# define SUCCESS 0
# define FAILURE 1

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
	INVALID_VECTOR = 2,
	MISSING_INPUT_VALUES = 3,
	COLOUR_VALUES_OUTSIDE_OF_RANGE = 4,
	AMBIENT_LIGHT_OUTSIDE_OF_RANGE = 5,
	LIGHT_BRIGHTNESS_RATIO_OUTSIDE_OF_RANGE = 6,
	CAMERA_FOV_OUTSIDE_OF_RANGE = 7,
}	t_Error;

typedef struct s_Vector3
{
	float		x;
	float		y;
	float		z;
}	t_Vector3;

typedef struct s_Colour
{
	int			r;
	int			g;
	int			b;
}	t_Colour;

typedef struct s_AmbientLight
{
	float		ratio;
	t_Colour	colour;
}	t_AmbientLight;

typedef struct s_Camera
{
	t_Vector3	position;
	t_Vector3	orientation;
	float		fov;
}	t_Camera;

typedef struct s_Light
{
	t_Vector3	position;
	float		brightness;
	t_Colour	colour;
}	t_Light;

typedef struct s_Sphere
{
	t_Vector3	centre;
	float		diameter;
	t_Colour	colour;
}	t_Sphere;

typedef struct s_Plane
{
	t_Vector3	point;
	t_Vector3	normal;
	t_Colour	colour;
}	t_Plane;

typedef struct s_Cylinder
{
	t_Vector3	centre;
	t_Vector3	axis;
	float		diameter;
	float		height;
	t_Colour	colour;
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
	int				width;
	int				height;
	int				**z_matrix;
	int				zoom;
	int				colour;
	int				amplify;
	int				shift_x;
	int				shift_y;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	unsigned int	*img_data;
	int				bpp;
	int				size_line;
	int				endian;
}			t_Mlx;

typedef struct s_Scene
{
	t_AmbientLight	ambient_light;
	t_Camera		camera;
	t_Light			light;
	struct Object	*objects;
	int				object_count;
	t_Mlx			mlx;
}	t_Scene;

// PROTOTYPES //

// error.c //
int			err_exit(t_Error error);
int			err_free_exit(struct Object *current, t_Scene *scene);
int			err_return(const char *message);

// file_check.c //
int			file_exists(char *filename);
int			file_status(const char *filename);
int			filename_error(char	*filename);

// get_next_line_utils.c //
size_t		gnl_strlen(const char *str);
char		*gnl_strchr(char *str, int target_char);
char		*gnl_strjoin(char *first_str, char *second_str);
char		*gnl_initialise_str(void);

// get_next_line.c //
char		*read_and_append_lines(int fd, char	*stash);
char		*extract_line_from_stash(char	*stash);
char		*remaining_stash_after_extraction(char *stash);
char		*get_next_line(int fd, char **line);

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
int			parse_ambient_light(char *line, t_AmbientLight *ambient_light);
int			parse_camera(char *line, t_Camera *camera);
int			parse_light(char *line, t_Light *light);

// parse_main.c //
int			parse_rt_file(const char *filename, t_Scene *scene);
int			parse_line(char	*line, t_Scene *scene);
//int			free_and_return(struct Object *obj, int ret_val);

// parse_objects.c //
int			parse_sphere(char *line, t_Scene *scene);
int			parse_plane(char *line, t_Scene *scene);
int			parse_cylinder(char *line, t_Scene *scene);

// parse_utils.c //
float		parse_float(char **str);
int			parse_int(char	**str);
int			parse_vector3(char *str, t_Vector3 *vec);
int			parse_colour(char *str, t_Colour *colour);
int			get_next_token(char **token);

// print_elements.c //
void		print_ambient_light(t_AmbientLight *ambient);
void		print_camera(const t_Camera *camera);
void		print_light(const t_Light *light);

// print_objects.c //
void		print_sphere(const struct Object *object);
void		print_plane(const struct Object *object);
void		print_cylinder(const struct Object *object);
void		print_all_objects(const t_Scene *scene);

// utils.c //
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

#endif