/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:50:33 by tday              #+#    #+#             */
/*   Updated: 2024/08/04 23:46:37 by tday             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

// # include "../mlx_linux/mlx.h"
# include "../libft/inc/libft.h"
# include "parsing.h"
# include "types.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <string.h>

typedef struct s_mrt
{
	t_amb		*amb;
	t_light		*light;
	t_cam		*cam;
	t_objs		*objs; // change to t_list later, just testing with single sphere
	int			width;
	int			height;
}				t_mrt;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_data // rename to mlx specific name
{
	void		*mlx;
	void		*win;
	int			height;
	int			width;
	t_img		img[2];
	int			draw_img;
	int			display_img;
}				t_data;

enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

/* initialisation */

void	init_window(t_data *data);
void	init_img(t_data *data);
t_mrt	*init_mrt(t_mrt *mrt);
void 	fill_mrt_defaults(t_mrt *mrt); // remove later

/* window */

int		close_window(t_data *data);

/* frame */

void	fill_background(t_data *data, int color);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	swap_images(t_data *data);
int		update_frame(t_data *data);
int		loop_function(t_data *data);

/* controls */

int		key_hook(int keycode, t_data *data);

/* ray_casting */
void	compute_ray_directions(t_mrt *mrt, t_cam *camera);

#endif
