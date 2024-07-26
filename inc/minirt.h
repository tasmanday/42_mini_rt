/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:50:33 by tday              #+#    #+#             */
/*   Updated: 2024/07/21 15:50:36 by tday             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../mlx_linux/mlx.h"
# include "../libft/inc/libft.h"
# include "parsing.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_mrt
{
	t_amb		*amb;
	t_light		*light;
	t_cam		*cam;
	t_list		*objs;
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

typedef struct s_coord
{
	float		x;
	float		y;
	float		z;
}				t_coord;

typedef struct s_rgb
{
	int			r;
	int			g;
	int			b;
}				t_rgb;


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

#endif
