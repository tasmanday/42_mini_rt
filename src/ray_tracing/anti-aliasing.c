/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti-aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 23:27:06 by tday              #+#    #+#             */
/*   Updated: 2025/04/11 22:21:00 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

/*
	Summary
	Calculates the final pixel color by averaging the colors from the four
	corner rays and converts it to a 32-bit ARGB format.

	Inputs
	[t_pixel*] pixel: Contains pointers to the four corner rays (tl, tr, bl, br)
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

	avg_r = (pixel->tl->colour.r + pixel->tr->colour.r + \
				pixel->bl->colour.r + pixel->br->colour.r \
				) * 0.25f;
	avg_g = (pixel->tl->colour.g + pixel->tr->colour.g + \
				pixel->bl->colour.g + pixel->br->colour.g \
				) * 0.25f;
	avg_b = (pixel->tl->colour.b + pixel->tr->colour.b + \
				pixel->bl->colour.b + pixel->br->colour.b \
				) * 0.25f;
	pixel->avg_colour = fill_rgb(avg_r, avg_g, avg_b, 255);
}

/*
	Summary
	Converts floating-point RGB color values [0-1] and alpha value into a
	32-bit ARGB color format.

	Inputs
	[float] r: Red component (0.0 to 1.0).
	[float] g: Green component (0.0 to 1.0).
	[float] b: Blue component (0.0 to 1.0).
	[unsigned int] alpha: Alpha component (0-255).

	Outputs
	[unsigned int] Returns a 32-bit color value in ARGB format.

	Explanation
	1. Convert Color Components:
	   - Scale RGB from [0-1] to [0-255]
	   - Cast to unsigned int

	2. Pack into 32-bit Format:
	   alpha << 24: Moves alpha to bits 24-31
	   |           Combines with...
	   red << 16:  Moves red to bits 16-23
	   |           Combines with...
	   green << 8: Moves green to bits 8-15
	   |           Combines with...
	   blue:       Already in bits 0-7

	Final format: AAAA AAAA RRRR RRRR GGGG GGGG BBBB BBBB
	             [alpha  ] [red    ] [green  ] [blue   ]
*/
unsigned int	fill_rgb(float r, float g, float b, unsigned int alpha)
{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;

	red = (unsigned int)(r * 255);
	green = (unsigned int)(g * 255);
	blue = (unsigned int)(b * 255);
	return ((alpha << 24) | (red << 16) | (green << 8) | blue);
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
