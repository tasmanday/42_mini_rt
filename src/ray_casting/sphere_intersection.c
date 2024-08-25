/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 22:09:09 by tday              #+#    #+#             */
/*   Updated: 2024/08/25 00:10:24 by tday             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

bool	ray_intersects_sphere(t_cam *camera, t_vect ray_dir, t_objs *sphere, \
	double *distance)
{
	t_vect	sphere_center;
	double	radius;

	sphere_center = *(sphere->coordinates);
	radius = sphere->diameter / 2.0;

	t_vect L = vect_subtract(*camera->coordinates, sphere_center);
	float	tc = vect_dot(L, ray_dir);
	if (tc < 0.0)
		return false; // Ray is pointing away from the sphere
	float d2 = (tc * tc) - vect_dot(L, L);
	float radius2 = radius * radius;
	if (d2 > radius2)
		return false;  // Ray misses the sphere
	float t1c = sqrt(radius2 - d2);
	float t1 = tc - t1c;
    float t2 = tc + t1c;
	// Find the closest intersection
    if (t1 > 0)
	{
        *distance = t1;  // t1 is the closest positive intersection point
		return true; // Intersection found
	}
    else if (t2 > 0)
	{
        *distance = t2;  // t1 is negative, so t2 is the closest positive intersection
		return true; // Intersection found
	}
    else
        return false;  // Both t1 and t2 are negative, no intersection in front of the camera
}
