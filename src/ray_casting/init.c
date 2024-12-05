/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:06:45 by tday              #+#    #+#             */
/*   Updated: 2024/12/05 17:51:16 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

t_pixel **allocate_pixel_array(int width, int height)
{
	t_pixel **pixels = safe_malloc(height * sizeof(t_pixel *), \
		"pixels array malloc error");
	int i = 0;
	while (i < height)
	{
		pixels[i] = safe_malloc(width * sizeof(t_pixel), \
			"pixels array malloc error");
		i++;
	}
	return pixels;
}

t_ray **allocate_corner_array(int width, int height)
{
	t_ray **corners = safe_malloc((height + 1) * sizeof(t_ray *), \
		"corners array malloc error");
	int i = 0;
	while (i <= height)
	{
		corners[i] = safe_malloc((width + 1) * sizeof(t_ray), \
			"corners array malloc error");
		i++;
	}
	return corners;
}

void	init_mem(t_mem *mem, t_Scene *scene)
{
	mem->pixels = allocate_pixel_array(scene->mlx.width, scene->mlx.height);
	mem->corners = allocate_corner_array(scene->mlx.width, scene->mlx.height);
}
