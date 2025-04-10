/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti-aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 23:27:06 by tday              #+#    #+#             */
/*   Updated: 2025/04/10 01:57:17 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

/*
	Summary
	Calculates the final pixel color by averaging the colors from the four
	corner rays and converts it to a 32-bit ARGB format.

	Inputs
	[t_pixel*] pixel: Contains pointers to the four corner rays (TL, TR, BL, BR)
		and storage for the final averaged color.

	Outputs
	None. Updates pixel->avg_colour with the final 32-bit color value.

	Explanation
	This function performs anti-aliasing by:
	1. Averaging RGB Components:
	   - Takes colors from all four corners (Top/Bottom Left/Right)
	   - Multiplies by 0.25 (divides by 4) to get the average
	   
	2. Color Conversion:
	   - Scales floating-point colors [0-1] to integer range [0-255]
	   - Combines components into 32-bit ARGB format using bit shifting
	   - Alpha is set to 255 (fully opaque)
*/
void	calculate_average_colour(t_pixel *pixel)
{
	float			avg_r;
	float			avg_g;
	float			avg_b;
	
	avg_r = (pixel->TL->colour.r + pixel->TR->colour.r + \
				pixel->BL->colour.r + pixel->BR->colour.r \
				) * 0.25f;
	avg_g = (pixel->TL->colour.g + pixel->TR->colour.g + \
				pixel->BL->colour.g + pixel->BR->colour.g \
				) * 0.25f;
	avg_b = (pixel->TL->colour.b + pixel->TR->colour.b + \
				pixel->BL->colour.b + pixel->BR->colour.b \
				) * 0.25f;
	pixel->avg_colour = fill_rgb(avg_r, avg_g, avg_b, 255);
}

unsigned int	fill_rgb(float r, float g, float b, unsigned int alpha)
{
	unsigned int	red = (unsigned int)(r * 255);
	unsigned int	green = (unsigned int)(g * 255);
	unsigned int	blue = (unsigned int)(b * 255);
	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

/*
	Summary
	Applies anti-aliasing to the entire image by averaging the corner ray
	colors for each pixel.

	Inputs
	[t_mem*] mem: Contains the pixel array with corner ray information.
	[t_Scene*] scene: Contains the image dimensions.

	Outputs
	None. Updates each pixel's average color in the pixel array.

	Explanation
	This function performs the final step of the rendering process:
	1. Iterates through every pixel in the image
	2. For each pixel, averages its four corner ray colors
	3. Converts the result to the final display format

	This simple form of anti-aliasing helps reduce jagged edges and improves
	image quality with minimal performance impact.
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
