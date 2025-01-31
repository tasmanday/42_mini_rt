/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:47:47 by tday              #+#    #+#             */
/*   Updated: 2025/01/31 23:36:31 by tday             ###   ########.fr       */
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
	init_pixel_array(mem, scene); // TODO move
	printf("init_pixel_array called\n"); // TODO remove
	render_scene(mem, scene);
	printf("render_scene called\n"); // TODO remove
	average_pixel_colours(mem, scene);
	printf("average_pixel_colours called\n"); // TODO remove
}
