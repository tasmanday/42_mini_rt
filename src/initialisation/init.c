/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:36:35 by tday              #+#    #+#             */
/*   Updated: 2024/08/25 00:43:11 by tday             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_mrt	*init_mrt(t_mrt *mrt)
{
	mrt->amb = safe_calloc(1, sizeof(t_amb), "amb malloc error");
	mrt->light = safe_calloc(1, sizeof(t_light), "light malloc error");
	mrt->cam = safe_calloc(1, sizeof(t_cam), "cam malloc error");
	return (mrt);
}

/* default valuse for testing */
void fill_mrt_defaults(t_mrt *mrt)
{
    // Fill ambient light
    mrt->amb->id = strdup("A");
    mrt->amb->ratio = 0.2f;
    mrt->amb->rgb = safe_calloc(1, sizeof(t_rgb), "amb rgb malloc error");
    mrt->amb->rgb->r = 255;
    mrt->amb->rgb->g = 255;
    mrt->amb->rgb->b = 255;

    // Fill camera
    mrt->cam->id = strdup("C");
    mrt->cam->coordinates = safe_calloc(1, sizeof(t_vect), "cam coordinates malloc error");
    mrt->cam->coordinates->x = 0.0f;
    mrt->cam->coordinates->y = 0.0f;
    mrt->cam->coordinates->z = 0.0f;
    mrt->cam->orientation = safe_calloc(1, sizeof(t_vect), "cam norm_vector malloc error");
    mrt->cam->orientation->x = 0.0f;
    mrt->cam->orientation->y = 0.0f;
    mrt->cam->orientation->z = -1.0f;
    mrt->cam->fov = 90;

    // Fill light
    mrt->light->id = strdup("L");
    mrt->light->coordinates = safe_calloc(1, sizeof(t_vect), "light coordinates malloc error");
    mrt->light->coordinates->x = -40.0f;
    mrt->light->coordinates->y = 0.0f;
    mrt->light->coordinates->z = 30.0f;
    mrt->light->ratio = 0.7f;
    mrt->light->rgb = safe_calloc(1, sizeof(t_rgb), "light rgb malloc error");
    mrt->light->rgb->r = 255;
    mrt->light->rgb->g = 255;
    mrt->light->rgb->b = 255;

    // Fill object (sphere)
    mrt->objs = safe_calloc(1, sizeof(t_objs), "objs malloc error");
    mrt->objs->id = strdup("sp");
    mrt->objs->coordinates = safe_calloc(1, sizeof(t_vect), "objs coordinates malloc error");
    mrt->objs->coordinates->x = 0.0f;
    mrt->objs->coordinates->y = 0.0f;
    mrt->objs->coordinates->z = -10.0f;
    mrt->objs->axis_vector = NULL; // Not needed for sphere
    mrt->objs->diameter = 10.0f;
    mrt->objs->height = 0.0f; // Not needed for sphere
    mrt->objs->rgb = safe_calloc(1, sizeof(t_rgb), "objs rgb malloc error");
    mrt->objs->rgb->r = 77;
    mrt->objs->rgb->g = 220;
    mrt->objs->rgb->b = 255;

	mrt->width = 1920;
	mrt->height = 1080;
}

/*
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
*/
