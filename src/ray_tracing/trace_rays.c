/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:47:47 by tday              #+#    #+#             */
/*   Updated: 2025/02/02 14:14:37 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

/*
	Summary
	Sets the color of a ray based on the type of the closest intersected object.

	Inputs
	[t_ray*] ray: The ray whose color is to be set.

	Outputs
	None. The color is set in the ray structure.

	Explanation
	This function assigns the initial color to a ray before lighting calculations.
	Each object in the scene stores its own base color, and this function
	retrieves that color based on the object type.

	This base color will later be modified by:
	- Light intensity calculations
	- Shadow effects
	- Ambient lighting
*/
void	set_ray_colour(t_ray *ray)
{
	if (ray->closest_object->type == SPHERE)
		ray->colour = ray->closest_object->u_data.sphere.colour;
	else if (ray->closest_object->type == PLANE)
		ray->colour = ray->closest_object->u_data.plane.colour;
	else if (ray->closest_object->type == CYLINDER)
		ray->colour = ray->closest_object->u_data.cylinder.colour;
}

/*
	Summary
	Renders the entire scene by processing each pixel through ray tracing.

	Inputs
	[t_mem*] mem: Pointer to memory structure containing ray data for each pixel.
	[t_Scene*] scene: Pointer to scene structure containing scene configuration
	                  and object data.

	Outputs
	None. Updates the ray data with color and intersection information for each
	pixel.

	Explanation
	This function implements the core ray tracing loop, processing each pixel
	in the image.
	For each pixel it:

	1. Checks for Object Intersection:
	   - Tests if the ray from that pixel hits any object in the scene
	   - NULL parameter means we're not ignoring any objects (used for shadows)

	2. If an Intersection Occurs:
	   - Calculates intersection details
	   - Sets the base color from the intersected object
	   - Applies lighting calculations and shadows

	The nested loops ensure every pixel in the image is processed, with the
	outer loop handling rows (y) and the inner loop handling columns (x).
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
			if (ray_intersects_object(scene, &mem->corner_ray[y][x], NULL))
			{
				calculate_intersection(&mem->corner_ray[y][x]);
				set_ray_colour(&mem->corner_ray[y][x]);
				apply_light_or_shadow(scene, &mem->corner_ray[y][x]);
			}
			x++;
		}
		y++;
	}
}

/*
	Summary
	Main ray tracing function that coordinates the rendering process.

	Inputs
	[t_mem*] mem: Pointer to memory structure containing ray and pixel data.
	[t_Scene*] scene: Pointer to scene structure containing scene configuration.

	Outputs
	None. Updates the pixel colors in the memory structure based on ray tracing
	calculations.

	Explanation
	This function implements a two-phase rendering approach:

	1. Corner Ray Tracing:
	   - Traces rays through the corners of each pixel instead of centers
	   - Calculates intersections, lighting, and shadows for each ray
	   - Requires one extra row and column of rays compared to center sampling

	2. Anti-aliasing:
	   - Averages the corner ray colors to produce the final pixel color
	   - Provides improved image quality with minimal performance impact
	   - Smooths edges and reduces aliasing artifacts

	This corner-sampling approach was chosen because it offers a good balance
	between image quality and performance, requiring only slightly more rays
	than center-sampling while providing built-in anti-aliasing capabilities.
*/
void	trace_rays(t_mem *mem, t_Scene *scene)
{
	init_pixel_array(mem, scene); // TODO move
	render_scene(mem, scene);
	average_pixel_colours(mem, scene);
}
