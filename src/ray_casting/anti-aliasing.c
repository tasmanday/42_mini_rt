/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti-aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 23:27:06 by tday              #+#    #+#             */
/*   Updated: 2025/02/01 00:15:05 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

void	calculate_average_colour(t_pixel *pixel)
{
	float	avg_r;
	float	avg_g;
	float	avg_b;
	unsigned int alpha = 255;

	avg_r = (pixel->TL->colour.r + pixel->TR->colour.r + \
				pixel->BL->colour.r + pixel->BR->colour.r \
				) * 0.25f;
	avg_g = (pixel->TL->colour.g + pixel->TR->colour.g + \
				pixel->BL->colour.g + pixel->BR->colour.g \
				) * 0.25f;
	avg_b = (pixel->TL->colour.b + pixel->TR->colour.b + \
				pixel->BL->colour.b + pixel->BR->colour.b \
				) * 0.25f;
	unsigned int r = (unsigned int)(avg_r * 255);
	unsigned int g = (unsigned int)(avg_g * 255);
	unsigned int b = (unsigned int)(avg_b * 255);
	pixel->avg_colour = (alpha << 24) | (r << 16) | (g << 8) | b;
}


/*
	Summary
	Calculates the average colour for each pixel in the grid.

	Inputs
	[t_mem*] mem: The memory structure containing the pixel array.
	[t_Scene*] scene: The scene containing the dimensions for the grid.

	Outputs
	None. The average colour is stored in each pixel structure.
*/
void	average_pixel_colours(t_mem *mem, t_Scene *scene)
{
	int	y;
	int	x;

	y = 0;
	while (y < scene->mlx.height)
	{
		x = 0;
		while (x < scene->mlx.width)
		{
			calculate_average_colour(&mem->pixels[y][x]); 
			x++;
		}
		y++;
	}
}
