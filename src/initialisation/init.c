/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:36:35 by tday              #+#    #+#             */
/*   Updated: 2024/07/20 00:00:53 by tday             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void init_window(t_data *data)
{
	data->width = 1920;
	data->height = 1080;
}

void init_img(t_data *data)
{
    data->img[0].img = mlx_new_image(data->mlx, data->width, data->height);
    data->img[0].addr = mlx_get_data_addr(data->img[0].img, &data->img[0].bits_per_pixel, &data->img[0].line_length, &data->img[0].endian);
    data->img[1].img = mlx_new_image(data->mlx, data->width, data->height);
    data->img[1].addr = mlx_get_data_addr(data->img[1].img, &data->img[1].bits_per_pixel, &data->img[1].line_length, &data->img[1].endian);
    data->draw_img = 0;
	data->display_img = 1;
}

