/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:49:10 by tday              #+#    #+#             */
/*   Updated: 2024/11/17 15:03:40 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

bool check_end_plane_intersection(t_Vector3 ray_origin, t_Vector3 ray_dir, 
                                  t_Cylinder *cylinder, float *distance)
{
    float cap_distance;
    bool hit = false;

    // Bottom cap
    t_Vector3 bottom_cap_center = cylinder->centre;
    if (ray_intersects_plane(ray_origin, ray_dir, bottom_cap_center, cylinder->axis, &cap_distance) &&
        vect_distance(vect_add(ray_origin, vect_multiply_scalar(ray_dir, cap_distance)), bottom_cap_center) <= cylinder->diameter / 2)
    {
        *distance = cap_distance;
        hit = true;
    }

    // Top cap
    t_Vector3 top_cap_center = vect_add(bottom_cap_center, vect_multiply_scalar(cylinder->axis, cylinder->height));
    if (ray_intersects_plane(ray_origin, ray_dir, top_cap_center, cylinder->axis, &cap_distance) &&
        vect_distance(vect_add(ray_origin, vect_multiply_scalar(ray_dir, cap_distance)), top_cap_center) <= cylinder->diameter / 2)
    {
        if (!hit || cap_distance < *distance)
        {
            *distance = cap_distance;
            hit = true;
        }
    }

    return hit;
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
	t_Vector3 bottom_cap_center = cylinder->centre;
	if (ray_intersects_plane(scene, ray_dir, &cap_distance) && \
		vect_distance(vect_add(ray_origin, vect_multiply(ray_dir, cap_distance)), bottom_cap_center) <= cylinder->diameter / 2)
	{
		*distance = cap_distance;
		hit_cap = true;
	}

	// Top cap
	t_Vector3 top_cap_center = vect_add(bottom_cap_center, vect_multiply(cylinder->axis, cylinder->height));
	if (ray_intersects_plane(scene, ray_dir, &cap_distance) && \
		vect_distance(vect_add(ray_origin, vect_multiply(ray_dir, cap_distance)), top_cap_center) <= cylinder->diameter / 2)
	{
		if (!hit_cap || cap_distance < *distance)
		{
			*distance = cap_distance;
			hit_cap = true;
		}
	}

	// Step 2: Check intersection with the cylinder's curved surface
	t_Vector3 oc = vect_subtract(ray_origin, cylinder->centre);
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
			float dist_to_axis = vect_dot(vect_subtract(intersection, cylinder->centre), cylinder->axis);

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
