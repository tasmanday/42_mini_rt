/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:47:47 by tday              #+#    #+#             */
/*   Updated: 2024/12/05 23:54:24 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

void	init_pixel_array(t_mem *mem, t_Scene *scene)
{
	int		y;
	int		x;

	// put in init_corner_rays() function
	y = 0;
	while (y <= scene->mlx.height)
	{
		x = 0;
		while (x <= scene->mlx.width)
		{
			init_ray(scene, &mem->corners[y][x], x, y);
			x++;
		}
		y++;
	}

	// put in init_pixels() function
	y = 0;
	while (y < scene->mlx.height)
	{
		x = 0;
		while (x < scene->mlx.width)
		{
			mem->pixels[y][x].TL = &mem->corners[y][x]; // top left corner
			mem->pixels[y][x].TR = &mem->corners[y][x + 1]; // top right corner
			mem->pixels[y][x].BL = &mem->corners[y + 1][x]; // bottom left corner
			mem->pixels[y][x].BR = &mem->corners[y + 1][x + 1]; // bottom right corner

			init_ray(scene, &mem->pixels[y][x].mid, x + 0.5, y + 0.5);

			mem->pixels[y][x].avg_colour = 0x000000;
			x++;
		}
		y++;
	}

}

void	check_corner_intersections(t_mem *mem, t_Scene *scene)
{
	int y, x;

	y = 0;
	while (y <= scene->mlx.height)
	{
		x = 0;
		while (x <= scene->mlx.width)
		{
			check_object_intersection(scene, &mem->corners[y][x]);
			x++;
		}
		y++;
	}
}

void	check_mid_intersections(t_mem *mem, t_Scene *scene)
{
	int y, x;

	y = 0;
	while (y < scene->mlx.height)
	{
		x = 0;
		while (x < scene->mlx.width)
		{
			check_object_intersection(scene, &mem->pixels[y][x].mid);
			x++;
		}
		y++;
	}
}

void	average_pixel_colours(t_mem *mem, t_Scene *scene)
{
	int y, x;

	y = 0;
	while (y < scene->mlx.height)
	{
		x = 0;
		while (x < scene->mlx.width)
		{
			int	avg_r = (mem->pixels[y][x].TL->colour.r +
							mem->pixels[y][x].TR->colour.r +
							mem->pixels[y][x].BL->colour.r +
							mem->pixels[y][x].BR->colour.r +
							mem->pixels[y][x].mid.colour.r) / 5;

			int	avg_g = (mem->pixels[y][x].TL->colour.g +
							mem->pixels[y][x].TR->colour.g +
							mem->pixels[y][x].BL->colour.g +
							mem->pixels[y][x].BR->colour.g +
							mem->pixels[y][x].mid.colour.g) / 5;

			int	avg_b = (mem->pixels[y][x].TL->colour.b +
							mem->pixels[y][x].TR->colour.b +
							mem->pixels[y][x].BL->colour.b +
							mem->pixels[y][x].BR->colour.b +
							mem->pixels[y][x].mid.colour.b) / 5;

			mem->pixels[y][x].avg_colour = avg_r << 16 | avg_g << 8 | avg_b;
			x++;
		}
		y++;
	}
}

void	trace_rays(t_mem *mem, t_Scene *scene)
{
	init_pixel_array(mem, scene);
	check_corner_intersections(mem, scene);
	check_mid_intersections(mem, scene);
	average_pixel_colours(mem, scene);
}
