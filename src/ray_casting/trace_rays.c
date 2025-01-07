/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:47:47 by tday              #+#    #+#             */
/*   Updated: 2025/01/07 22:46:20 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/*	
	ONLY USE THIS IF CALCULATE_AVERAGE_COLOUR GETS TOO LONG!
	-> Added to apply ambient light
	Takes each colour component of the base colour and multiplies it
	by the ambient light ratio AND colour and divides the result by 255 to keep
	it in range. f_min is then used to ensure no volour value exceeds 225
	(maximum brightness).

t_Colour4   apply_ambient_light(t_Colour4 base_colour, t_AmbientLight ambient)
{
	t_Colour4    result;

	result.r = base_colour.r * (ambient.ratio * ambient.colour.r /  255.0);
	result.g = base_colour.g * (ambient.ratio * ambient.colour.g /  255.0);
	result.b = base_colour.b * (ambient.ratio * ambient.colour.b /  255.0);
	
    result.r = fmin(result.r, 255.0);
    result.g = fmin(result.g, 255.0);
    result.b = fmin(result.b, 255.0);
    return (result);
}
*/

/*
	Summary
	Initializes rays for each corner of the pixel grid.

	Inputs
	[t_mem*] mem: The memory structure containing the corner array.
	[t_Scene*] scene: The scene containing the dimensions for the grid.

	Outputs
	None. The corner rays are initialized in the memory structure.
*/
void	init_corner_rays(t_mem *mem, t_Scene *scene)
{
	int		y;
	int		x;

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
}

/*
	Summary
	Initializes the pixel array with corner references and mid-point rays.

	Inputs
	[t_mem*] mem: The memory structure containing the pixel and corner arrays.
	[t_Scene*] scene: The scene containing the dimensions for the grid.

	Outputs
	None. The pixel array is initialized with corner references and mid-point
	rays.
*/
void	init_pixels(t_mem *mem, t_Scene *scene)
{
	int		y;
	int		x;

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

/*
	Summary
	Initializes the pixel and corner arrays for ray tracing.

	Inputs
	[t_mem*] mem: The memory structure to initialize.
	[t_Scene*] scene: The scene containing the dimensions for the arrays.

	Outputs
	None. The memory structure is initialized with pixel and corner arrays.
*/
void	init_pixel_array(t_mem *mem, t_Scene *scene)
{
	init_corner_rays(mem, scene);
	init_pixels(mem, scene);
}

/*
	Summary
	Checks for intersections between scene objects and corner rays.

	Inputs
	[t_mem*] mem: The memory structure containing the corner rays.
	[t_Scene*] scene: The scene containing the objects to check against.

	Outputs
	None. Intersection data is stored in the corner rays.
*/
void	check_corner_intersections(t_mem *mem, t_Scene *scene)
{
	int		y;
	int		x;

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

/*
	Summary
	Checks for intersections between scene objects and mid-point rays of pixels.

	Inputs
	[t_mem*] mem: The memory structure containing the pixel rays.
	[t_Scene*] scene: The scene containing the objects to check against.

	Outputs
	None. Intersection data is stored in the mid-point rays.
*/
void	check_mid_intersections(t_mem *mem, t_Scene *scene)
{
	int		y;
	int		x;

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

/*
	Summary
	Calculates the average colour of a pixel based on its corner and mid-point
	rays.

	Inputs
	[t_pixel*] pixel: The pixel whose average colour is to be calculated.

	Outputs
	None. The average colour is stored in the pixel structure.
*/
//void	calculate_average_colour(t_pixel *pixel) // New prototype below (now takes t_AmbientLight)
void calculate_average_colour(t_pixel *pixel, t_AmbientLight ambient)
{
	float	avg_r;
	float	avg_g;
	float	avg_b;
	//unsigned int alpha = 255; // This is now further down

	avg_r = (pixel->TL->colour.r + pixel->TR->colour.r + \
				pixel->BL->colour.r + pixel->BR->colour.r + \
				pixel->mid.colour.r) / 5;
	avg_g = (pixel->TL->colour.g + pixel->TR->colour.g + \
				pixel->BL->colour.g + pixel->BR->colour.g + \
				pixel->mid.colour.g) / 5;
	avg_b = (pixel->TL->colour.b + pixel->TR->colour.b + \
				pixel->BL->colour.b + pixel->BR->colour.b + \
				pixel->mid.colour.b) / 5;
	// NEW! Added from here...
	avg_r = avg_r * (1 - ambient.ratio) + ambient.colour.r * ambient.ratio; // 1st part (1 - ratio) is % of original colour e.g. 1 - 0.3 = 70%
    avg_g = avg_g * (1 - ambient.ratio) + ambient.colour.g * ambient.ratio; // 2nd part is ratio % of ambient colour
    avg_b = avg_b * (1 - ambient.ratio) + ambient.colour.b * ambient.ratio; // Result is final blended colour
    avg_r = fminf(fmaxf(avg_r, 0.0f), 1.0f); // Clamps value between 0 and 1 so not too bright/dark
    avg_g = fminf(fmaxf(avg_g, 0.0f), 1.0f);
    avg_b = fminf(fmaxf(avg_b, 0.0f), 1.0f);
    unsigned int alpha = 255;
	// ...until here to apply ambient light
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
			//calculate_average_colour(&mem->pixels[y][x]); // Now the below line to account for ambient light
			calculate_average_colour(&mem->pixels[y][x], scene->ambient_light);
			x++;
		}
		y++;
	}
	printf(G"-> Ambient light adjustment applied\n"RST);
}

/*
	Summary
	Traces rays through the scene, checking intersections and calculating pixel
	colours.

	Inputs
	[t_mem*] mem: The memory structure containing the pixel and corner arrays.
	[t_Scene*] scene: The scene to trace rays through.

	Outputs
	None. The pixel colours are calculated and stored in the memory structure.
*/
void	trace_rays(t_mem *mem, t_Scene *scene)
{
	init_pixel_array(mem, scene);
	check_corner_intersections(mem, scene);
	check_mid_intersections(mem, scene);
	average_pixel_colours(mem, scene);
}
