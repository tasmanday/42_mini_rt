/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:14:55 by tday              #+#    #+#             */
/*   Updated: 2025/04/11 22:16:08 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

/*
	Summary
	Determines if a ray intersects with a cylinder and finds the closest
	intersection point.

	Inputs
	[t_ray*] ray: The ray being checked for intersection.
	[t_Cylinder] cyl: The cylinder to check against.
	[float*] distance: Pointer to store the closest intersection distance.

	Outputs
	[bool] Returns true if there is an intersection, false otherwise.
	Also updates distance and ray->cyl_closest_point for the closest hit.

	Explanation
	This function coordinates the complete cylinder intersection test:
	1. Initialization:
	   - Normalizes cylinder axis
	   - Creates array for up to 4 intersection points (2 caps, 2 body)
	   
	2. Intersection Tests:
	   - Checks end caps (points[0] and points[1])
	   - Checks cylinder body (points[2] and points[3])
	   
	3. Find Closest Hit:
	   - Examines all valid intersection points (distance > 0)
	   - Updates distance if closer hit is found
	   - Records which part was hit (caps or body) in cyl_closest_point
*/
bool	ray_intersects_cyl(t_ray *ray, t_Cylinder cyl, float *distance)
{
	float	points[4];
	bool	intersection_flag;
	int		i;

	cyl.axis = vect_normalise(cyl.axis);
	points[0] = -1;
	points[1] = -1;
	points[2] = -1;
	points[3] = -1;
	intersection_flag = false;
	check_end_cap(ray, cyl, points);
	check_cylinder_body(ray, cyl, points);
	i = 0;
	while (i < 4)
	{
		if (points[i] > 0 && points[i] < *distance)
		{
			*distance = points[i];
			intersection_flag = true;
			ray->cyl_closest_point = i;
		}
		i++;
	}
	return (intersection_flag);
}
