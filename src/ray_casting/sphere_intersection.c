/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 22:09:09 by tday              #+#    #+#             */
/*   Updated: 2024/08/25 17:08:21 by tday             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

bool	ray_intersects_sphere(t_Scene *scene, t_Vector3 ray_dir, 				\
		float *distance)
{
	t_Vector3	sphere_center;
	float	radius;


	sphere_center = (scene->objects->u_data.sphere.centre);
	radius = scene->objects->u_data.sphere.diameter / 2.0;
//	printf("%f", radius);

	t_Vector3 L = vect_subtract(scene->camera.position, sphere_center);
	float	tc = vect_dot(L, ray_dir);
	if (tc < 0.0)
		return (false); // Ray is pointing away from the sphere printf("Ray is pointing away from the sphere\n"),
	float l2 = vect_dot(L, L);
	float d2 = l2 - (tc * tc);
	float radius2 = radius * radius;
//	printf("l2 %f, tc %f, d2 %f, r2 %f ", l2, tc, d2, radius2);
	if (d2 > radius2)
		return (printf("_ "), false);  // Ray misses the sphere printf("Ray misses the sphere\n"),
	float t1c = sqrt(radius2 - d2);
	float t1 = tc - t1c;
    float t2 = tc + t1c;
	// Find the closest intersection
    if (t1 > 0)
	{
        *distance = t1;  // t1 is the closest positive intersection point
		return (printf("O "), true); // Intersection found printf("t1 closest intersection\n"), 
	}
    else if (t2 > 0)
	{
        *distance = t2;  // t1 is negative, so t2 is the closest positive intersection
		return (printf(". "), true); // Intersection found printf("t2 closest intersection\n"), 
	}
    else
        return (printf("* "), false);  // Both t1 and t2 are negative, no intersection in front of the camera printf("Both t1 and t2 are negative, no intersection in front of the camera\n"), 
}
