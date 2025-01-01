/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 22:09:09 by tday              #+#    #+#             */
/*   Updated: 2025/01/01 18:08:59 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

/*
	Summary
	Determines if a ray is pointing away from a sphere.

	Inputs
	[t_Vector3] l: Vector from the ray origin to the sphere center.
	[t_Vector3] ray_dir: The direction vector of the ray.

	Outputs
	[bool] Returns true if the ray is pointing away from the sphere, false
		otherwise.

	Notes
	- The function calculates the dot product of l and ray_dir. If the result
		is negative, the ray is pointing away.
*/
bool	ray_pointing_away(t_Vector3 l, t_Vector3 ray_dir)
{
	float	tc;

	tc = vect_dot(l, ray_dir);
	if (tc < 0.0)
		return (true);
	return (false);
}

/*
	Summary
	Determines if a ray misses a sphere based on the calculated distance.

	Inputs
	[float] l2: The squared length of vector l.
	[float] tc: The projection of l onto the ray direction.
	[float] radius2: The squared radius of the sphere.

	Outputs
	[bool] Returns true if the ray misses the sphere, false otherwise.

	Notes
	- The function calculates d2, the squared distance from the sphere center to
		the ray. If d2 is greater than radius2, the ray misses the sphere.
*/
bool	ray_misses_sphere(float l2, float tc, float radius2)
{
	float	d2;

	d2 = l2 - (tc * tc);
	if (d2 > radius2)
		return (true);
	return (false);
}

/*
	Summary
	Finds the closest intersection point of a ray with a sphere.

	Inputs
	[float] tc: The projection of l onto the ray direction.
	[float] radius2: The squared radius of the sphere.
	[float] d2: The squared distance from the sphere center to the ray.
	[float*] distance: Pointer to store the closest intersection distance.

	Outputs
	[bool] Returns true if an intersection is found, false otherwise.

	Notes
	- The function calculates two potential intersection points, t1 and t2.
		It returns the closest positive intersection.
	- t1c is the distance from the projection point (tc) to the intersection
		points along the ray direction. It is derived from the Pythagorean
		theorem, where t1c = sqrt(radius2 - d2). This represents the
		half-length of the chord formed by the intersection points on the ray.
*/
bool	find_closest_intersection(float tc, float radius2, float d2, \
	float *distance)
{
	float	t1c;
	float	t1;
	float	t2;

	t1c = sqrt(radius2 - d2);
	t1 = tc - t1c;
	t2 = tc + t1c;

	if (t1 > 0)
	{
		*distance = t1;
		return (true);
	}
	else if (t2 > 0)
	{
		*distance = t2;
		return (true);
	}
	return (false);
}

/*
	Summary
	Determines if a ray intersects with a sphere and calculates the intersection
	distance.

	Inputs
	[t_ray*] ray: The ray to check for intersection.
	[t_Sphere] sphere: The sphere to check against.
	[float*] distance: Pointer to store the intersection distance.

	Outputs
	[bool] Returns true if the ray intersects the sphere, false otherwise.

	Notes
	- The function calculates the vector l from the ray origin to the sphere
		center.
	- tc is the projection of vector l onto the ray direction, representing the
		closest approach of the ray to the sphere center along the ray's path.
	- It checks if the ray is pointing away or misses the sphere.
	- If an intersection is found, the closest intersection distance is stored.
*/
bool	ray_intersects_sphere(t_ray *ray, t_Sphere sphere, float *distance)
{
	float		radius;
	t_Vector3	l;
	float		tc;
	float		l2;
	float		radius2;

	radius = sphere.diameter / 2.0;
	l = vect_subtract(sphere.center, ray->ray_origin);
	tc = vect_dot(l, ray->ray_dir);
	if (ray_pointing_away(l, ray->ray_dir))
		return (false);
	l2 = vect_dot(l, l);
	radius2 = radius * radius;
	if (ray_misses_sphere(l2, tc, radius2))
		return (false);
	if (find_closest_intersection(tc, radius2, l2 - (tc * tc), distance))
		return (true);
	return (false);
}
