/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:47:47 by tday              #+#    #+#             */
/*   Updated: 2025/01/13 21:41:05 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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

// NEW! Shadow check function
bool is_in_shadow(t_Scene *scene, t_Vector3 intersection_point, t_Object *ignore_object)
{
	t_ray	shadow_ray;
	float	light_distance;

	// Create shdaow ray from insection point to light source
	shadow_ray.ray_origin = intersection_point;
	// Add offset to avoid self-shadowing
//	shadow_ray.ray_origin = vect_add(intersection_point, vect_multiply_scalar(normal, 0.00001f));
	// Calculate direction to light
	shadow_ray.ray_dir = vect_subtract(scene->light.position, intersection_point);

	shadow_ray.ray_origin = vect_add(intersection_point, vect_multiply_scalar(shadow_ray.ray_dir, 0.0001f));
	// Calculate distance to light
	light_distance = vect_distance(scene->light.position, intersection_point);
	// Normalise direction
	shadow_ray.ray_dir = vect_normalise(shadow_ray.ray_dir);

	shadow_ray.intersects_object = false;
	shadow_ray.closest_hit_distance = INFINITY;
	shadow_ray.closest_object = NULL;
	shadow_ray.cyl_closest_point = 0;

	// Check for insections between point and light
if (check_object_intersection(scene, &shadow_ray, ignore_object))
		{
			// If intersection is closer than the light, point is in shadow
			if (shadow_ray.closest_hit_distance < light_distance)
				return (true);
		}
/*	// Check for insections between point and light
	t_Object	*current = scene->objects;
	while (current)
	{
		if (check_object_intersection(scene, &shadow_ray))
		{
			// If intersection is closer than the light, point is in shadow
			if (shadow_ray.closest_hit_distance > 0.0001f && 
				shadow_ray.closest_hit_distance < light_distance)
				return (true);
		}
		current = current->next;
	} */
	return (false);
}

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

// TODO: fix comment after modifying function
/*
	Summary
	Checks for intersections between scene objects and corner rays.

	Inputs
	[t_mem*] mem: The memory structure containing the corner rays.
	[t_Scene*] scene: The scene containing the objects to check against.

	Outputs
	None. Intersection data is stored in the corner rays.
*/
void	render_scene(t_mem *mem, t_Scene *scene)
{
	int		y;
	int		x;


	y = 0;
	while (y <= scene->mlx.height)
	{
		x = 0;
		while (x <= scene->mlx.width)
		{
			if (check_object_intersection(scene, &mem->corners[y][x], NULL))
				calculate_ray_colour(scene, &mem->corners[y][x]);
			if (y < scene->mlx.height && x < scene->mlx.width)
			{
			 	if (check_object_intersection(scene, &mem->pixels[y][x].mid, NULL))
					calculate_ray_colour(scene, &mem->pixels[y][x].mid);
			}
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
} */

/*
	Summary
	Calculates the average colour of a pixel based on its corner and mid-point
	rays.

	Inputs
	[t_pixel*] pixel: The pixel whose average colour is to be calculated.

	Outputs
	None. The average colour is stored in the pixel structure.
*/
/*
// OLD -> This is the now redundant PRE shadow version.
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
*/

void	calculate_average_colour(t_pixel *pixel)
{
	float	avg_r;
	float	avg_g;
	float	avg_b;
	unsigned int alpha = 255;

	avg_r = (pixel->TL->colour.r + pixel->TR->colour.r + \
				pixel->BL->colour.r + pixel->BR->colour.r + \
				pixel->mid.colour.r) * 0.2f;
	avg_g = (pixel->TL->colour.g + pixel->TR->colour.g + \
				pixel->BL->colour.g + pixel->BR->colour.g + \
				pixel->mid.colour.g) * 0.2f;
	avg_b = (pixel->TL->colour.b + pixel->TR->colour.b + \
				pixel->BL->colour.b + pixel->BR->colour.b + \
				pixel->mid.colour.b) * 0.2f;
	unsigned int r = (unsigned int)(avg_r * 255);
	unsigned int g = (unsigned int)(avg_g * 255);
	unsigned int b = (unsigned int)(avg_b * 255);
	pixel->avg_colour = (alpha << 24) | (r << 16) | (g << 8) | b;
}

/* void calculate_average_colour(t_pixel *pixel)
{
    float   avg_r;
    float   avg_g;
    float   avg_b;

    // Calculate average from all sample points
    avg_r = (pixel->TL->colour.r + pixel->TR->colour.r + \
            pixel->BL->colour.r + pixel->BR->colour.r + \
            pixel->mid.colour.r) * 0.2f;
    avg_g = (pixel->TL->colour.g + pixel->TR->colour.g + \
            pixel->BL->colour.g + pixel->BR->colour.g + \
            pixel->mid.colour.g) * 0.2f;
    avg_b = (pixel->TL->colour.b + pixel->TR->colour.b + \
            pixel->BL->colour.b + pixel->BR->colour.b + \
            pixel->mid.colour.b) * 0.2f;
    // Check if point is in shadow    *** moved elsewhere ***
    if (pixel->mid.intersects_object)
    {
        t_Vector3 intersection_point = vect_add(pixel->mid.ray_origin, 
            vect_multiply_scalar(pixel->mid.ray_dir, pixel->mid.closest_hit_distance));
        if (is_in_shadow(scene, intersection_point, pixel->mid.normal_at_intersection))
        {
            // If in shadow, only use ambient light
            avg_r = avg_r * ambient.ratio;
            avg_g = avg_g * ambient.ratio;
            avg_b = avg_b * ambient.ratio;
        }
        else
        {
            // If not in shadow, use ambient light calculation
            avg_r = avg_r * (1 - ambient.ratio) + ambient.colour.r * ambient.ratio;
            avg_g = avg_g * (1 - ambient.ratio) + ambient.colour.g * ambient.ratio;
            avg_b = avg_b * (1 - ambient.ratio) + ambient.colour.b * ambient.ratio;
        }
    } 
    // Clamp values
    avg_r = fminf(fmaxf(avg_r, 0.0f), 1.0f);
    avg_g = fminf(fmaxf(avg_g, 0.0f), 1.0f);
    avg_b = fminf(fmaxf(avg_b, 0.0f), 1.0f);
    // Convert to final colour
    unsigned int alpha = 255;
    unsigned int r = (unsigned int)(avg_r * 255);
    unsigned int g = (unsigned int)(avg_g * 255);
    unsigned int b = (unsigned int)(avg_b * 255);
    pixel->avg_colour = (alpha << 24) | (r << 16) | (g << 8) | b;
} */

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
			//calculate_average_colour(&mem->pixels[y][x], scene->ambient_light); // Now the below for shadow
			//calculate_average_colour(&mem->pixels[y][x], scene->ambient_light, scene); // Now the above again because I moved shadow and ambient light
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
	render_scene(mem, scene);
	average_pixel_colours(mem, scene);
}
