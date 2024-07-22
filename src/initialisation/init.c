/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:36:35 by tday              #+#    #+#             */
/*   Updated: 2024/07/21 17:14:34 by tday             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_mrt	*init_mrt(t_mrt *mrt)
{
	mrt = safe_calloc(1, sizeof(t_mrt), "mrt malloc error");
	return (mrt);
}


void	init_window(t_data *data) // for mlx
{
	data->width = 1920;
	data->height = 1080;
}

void	init_img(t_data *data) // for mlx
{
	data->img[0].img = mlx_new_image(data->mlx, data->width, data->height);
	data->img[0].addr = mlx_get_data_addr(data->img[0].img, \
		&data->img[0].bits_per_pixel, &data->img[0].line_length, \
		&data->img[0].endian);
	data->img[1].img = mlx_new_image(data->mlx, data->width, data->height);
	data->img[1].addr = mlx_get_data_addr(data->img[1].img, \
		&data->img[1].bits_per_pixel, &data->img[1].line_length, \
		&data->img[1].endian);
	data->draw_img = 0;
	data->display_img = 1;
}

