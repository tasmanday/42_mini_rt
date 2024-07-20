/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:28:38 by tday              #+#    #+#             */
/*   Updated: 2024/07/20 20:50:28 by tday             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void swap_images(t_data *data)
{
    int temp = data->draw_img;
    data->draw_img = data->display_img;
    data->display_img = temp;
}

int update_frame(t_data *data)
{
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