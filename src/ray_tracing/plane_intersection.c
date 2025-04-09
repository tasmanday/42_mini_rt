/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:49:10 by tday              #+#    #+#             */
/*   Updated: 2025/04/10 00:57:39 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

/*
	Summary
	Determines if a ray intersects with a plane and calculates the intersection
	distance.

	Inputs
	[t_ray*] ray: The ray to check for intersection.
	[t_Vector3] point_on_plane: A point on the plane.
	[t_Vector3] plane_norm_vect: The normal vector of the plane.
	[float*] distance: Pointer to store the intersection distance.

	Outputs
	[bool] Returns true if the ray intersects the plane, false otherwise.

	Notes
	- If the denominator is close to zero, the ray is parallel to the plane,
		and no intersection occurs. returns false
	- If the calculated distance is positive, the intersection is in front of the
		camera. returns true
	- If the distance is negative, the intersection is behind the camera, and the
		distance is set to infinity. returns false
*/
bool	ray_intersects_plane(t_ray *ray, t_Vector3	point_on_plane, \
		t_Vector3	plane_norm_vect, float *distance)
{
	float		denominator;

	plane_norm_vect = vect_normalise(plane_norm_vect);
	denominator = vect_dot(plane_norm_vect, ray->ray_dir);
	if (fabs(denominator) < 1e-6)
		return (false);
	*distance = vect_dot(plane_norm_vect, \
		vect_subtract(point_on_plane, ray->ray_origin)) / denominator;
	if (*distance > 0)
		return (true);
	else
	{
		*distance = INFINITY;
		return (false);
	}
}
