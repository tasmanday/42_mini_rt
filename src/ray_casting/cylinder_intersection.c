/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:49:10 by tday              #+#    #+#             */
/*   Updated: 2024/11/21 22:15:17 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

bool	intersection_within_radius(t_ray *ray, t_Cylinder cylinder, t_Vector3 cap_center, float temp_distance)
{
	if (vect_distance(vect_add(ray->ray_origin, \
	vect_multiply_scalar(ray->ray_dir, temp_distance)), cap_center) \
	<= cylinder.diameter / 2)
		return (true);
	return (false);
}

float	*check_end_plane_intersection(t_ray *ray, t_Cylinder cylinder, float *distance)
{
	t_Vector3	offset;
	t_Vector3	cap_a_center;
	t_Vector3	cap_b_center;
	float		temp_distance;

	// Scale the normalised axis by half the height to get the offset
	offset = vect_multiply_scalar(cylinder.axis, cylinder.height / 2.0f);

	// cap a
	cap_a_center = vect_add(cylinder.center, offset);
	if (ray_intersects_plane(ray, cap_a_center, cylinder.axis, &temp_distance) \
	&& intersection_within_radius(ray, cylinder, cap_a_center, temp_distance))		
	{
		*distance = temp_distance;
	}

	// TODO cap b
	t_Vector3 cap_b_center = vect_subtract(cylinder.center, offset);
	if (ray_intersects_plane(ray, cap_b_center, cylinder.axis, &temp_distance) \
	&& intersection_within_radius(ray, cylinder, cap_a_center, temp_distance) \
	&& temp_distance < *distance)
	{
		*distance = temp_distance;
	}

	return (distance);
}


bool	ray_intersects_cylinder(t_Scene *scene, t_Vector3 ray_dir, \
		float *distance)
{
	t_Vector3 ray_origin = scene->camera.position;
	t_Cylinder *cylinder = &scene->objects->u_data.cylinder;

	// Step 1: Check intersection with cylinder caps (top and bottom planes)
	float cap_distance;
	bool hit_cap = false;

	// Bottom cap
	t_Vector3 cap_a_center = cylinder->center;
	if (ray_intersects_plane(scene, ray_dir, &cap_distance) && \
		vect_distance(vect_add(ray_origin, vect_multiply(ray_dir, cap_distance)), cap_a_center) <= cylinder->diameter / 2)
	{
		*distance = cap_distance;
		hit_cap = true;
	}

	// Top cap
	t_Vector3 cap_b_center = vect_add(cap_a_center, vect_multiply(cylinder->axis, cylinder->height));
	if (ray_intersects_plane(scene, ray_dir, &cap_distance) && \
		vect_distance(vect_add(ray_origin, vect_multiply(ray_dir, cap_distance)), cap_b_center) <= cylinder->diameter / 2)
	{
		if (!hit_cap || cap_distance < *distance)
		{
			*distance = cap_distance;
			hit_cap = true;
		}
	}

	// Step 2: Check intersection with the cylinder's curved surface
	t_Vector3 oc = vect_subtract(ray_origin, cylinder->center);
	t_Vector3 ray_dir_proj = vect_cross(ray_dir, cylinder->axis);
	t_Vector3 oc_proj = vect_cross(oc, cylinder->axis);

	float a = vect_dot(ray_dir_proj, ray_dir_proj);
	float b = 2 * vect_dot(ray_dir_proj, oc_proj);
	float c = vect_dot(oc_proj, oc_proj) - pow(cylinder->diameter / 2, 2);

	float discriminant = b * b - 4 * a * c;
	if (discriminant >= 0)
	{
		float sqrt_discriminant = sqrt(discriminant);
		float t1 = (-b - sqrt_discriminant) / (2 * a);
		float t2 = (-b + sqrt_discriminant) / (2 * a);

		float t = t1 > 0 ? t1 : (t2 > 0 ? t2 : -1);
		if (t > 0)
		{
			t_Vector3 intersection = vect_add(ray_origin, vect_multiply(ray_dir, t));
			float dist_to_axis = vect_dot(vect_subtract(intersection, cylinder->center), cylinder->axis);

			if (fabs(dist_to_axis) <= cylinder->height / 2)
			{
				if (!hit_cap || t < *distance)
				{
					*distance = t;
					hit_cap = true;
				}
			}
		}
	}

	return (hit_cap);
}
