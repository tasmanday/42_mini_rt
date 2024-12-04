/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:06:45 by tday              #+#    #+#             */
/*   Updated: 2024/12/04 23:34:20 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

t_pixel **allocate_pixel_array(int width, int height)
{
	t_pixel **pixels = malloc(height * sizeof(t_pixel *));
	int i = 0;
	while (i < height)
	{
		pixels[i] = malloc(width * sizeof(t_pixel));
		i++;
	}
	return pixels;
}

t_ray **allocate_corner_array(int width, int height)
{
	t_ray **corners = malloc((height + 1) * sizeof(t_ray *));
	int i = 0;
	while (i <= height)
	{
		corners[i] = malloc((width + 1) * sizeof(t_ray));
		i++;
	}
	return corners;
}

