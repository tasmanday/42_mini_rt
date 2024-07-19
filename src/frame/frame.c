/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:28:38 by tday              #+#    #+#             */
/*   Updated: 2024/07/19 22:30:32 by tday             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	fill_background(t_data *data, int colour)
{
	int		x;
	int		y;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			my_mlx_pixel_put(data, x, y, colour);
			x++;
		}
		y++;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int colour)
{
	char	*pixel;
	t_img	*img;

	if (x < 0 || x >= data->width || y < 0 || y >= data->height)
		return ;
	img = &data->img[data->draw_img];
	if (data->draw_img == 0)
		colour = 0x000000;
	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)pixel = colour;
}

void swap_images(t_data *data)
{
    int temp = data->draw_img;
    data->draw_img = data->display_img;
    data->display_img = temp;
}

int update_frame(t_data *data)
{
    fill_background(data, 0x00AAFF);
    mlx_put_image_to_window(data->mlx, data->win, 							\
		data->img[data->display_img].img, 0, 0);
    swap_images(data);
    return (0);
}

int loop_function(t_data *data)
{
    update_frame(data);
    return (0);
}