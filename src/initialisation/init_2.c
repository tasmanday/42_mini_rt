/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:52:59 by tday              #+#    #+#             */
/*   Updated: 2025/04/12 09:08:01 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/*
	Summary
	Initializes a ray with its origin, direction, and default intersection
	properties.

	Inputs
	[t_Scene*] scene: The scene containing the camera position.
	[t_ray*] ray: The ray to initialize.
	[int] x: The x-coordinate of the pixel.
	[int] y: The y-coordinate of the pixel.

	Outputs
	None. The ray is initialized with its properties.

	Explanation
	1. Set Ray Origin and Direction:
	   - Origin set to camera position
	   - Direction calculated based on pixel coordinates

	2. Initialize Intersection Properties:
	   - No intersection (false)
	   - Infinite hit distance
	   - No closest object (NULL)

	3. Set Initial Color:
	   - All color components (r,g,b) set to 0
*/
void	init_ray(t_Scene *scene, t_ray *ray, int x, int y)
{
	ray->ray_origin = scene->camera.position;
	ray->ray_dir = get_ray_direction(scene, x, y);
	ray->intersects_object = false;
	ray->closest_hit_distance = INFINITY;
	ray->closest_object = NULL;
	ray->colour.r = 0;
	ray->colour.g = 0;
	ray->colour.b = 0;
}
