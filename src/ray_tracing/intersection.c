/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 22:30:41 by tday              #+#    #+#             */
/*   Updated: 2025/02/01 17:06:48 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

/*
	Summary
	Checks if a ray intersects with a given object and updates the intersection
	distance.

	Inputs
	[t_ray*] ray: The ray to check for intersection.
	[t_Object*] object: The object to check against.
	[float*] distance: Pointer to store the intersection distance.

	Outputs
	[bool] Returns true if there is an intersection, false otherwise.
*/
bool	check_intersection(t_ray *ray, t_Object *object, float *distance)
{
	if (object->type == PLANE)
		return (ray_intersects_plane(ray, object->u_data.plane.point, \
			object->u_data.plane.normal, distance));
	else if (object->type == SPHERE)
		return (ray_intersects_sphere(ray, object->u_data.sphere, distance));
	else if (object->type == CYLINDER)
		return (ray_intersects_cylinder(ray, object->u_data.cylinder, \
			distance));
	return (false);
}

void	update_closest_object(t_ray *ray, t_Object *object, float distance)
{
	ray->closest_hit_distance = distance;
	ray->closest_object = object;
}

// TODO update comment
/* 
	Summary
	Checks for intersections between a ray and all objects in the scene.

	Inputs
	[t_Scene*] scene: The scene containing the objects.
	[t_ray*] ray: The ray to check for intersections.

	Outputs
	None. The ray's intersection properties are updated based on the closest
	intersection.
*/
bool	ray_intersects_object(t_Scene *scene, t_ray *ray, t_Object *ignore_obj)
{
	t_Object	*current_object;
	float		distance;
	bool		intersects;

	current_object = scene->objects;
	distance = INFINITY;
	ray->intersects_object = false;
	while (current_object)
	{
		if (current_object == ignore_obj)
		{
			current_object = current_object->next;
			continue;
		}
		intersects = check_intersection(ray, current_object, &distance);
		if (intersects)
		{
			ray->intersects_object = true;
			if (distance < ray->closest_hit_distance)
				update_closest_object(ray, current_object, distance);
		}
		current_object = current_object->next;
	}
	return (ray->intersects_object);
}

void	calculate_intersection_point(t_ray *ray)
{
	t_Vector3	ray_length;
	
	ray_length = vect_multiply_scalar(ray->ray_dir, ray->closest_hit_distance);
	ray->intersection_point = vect_add(ray->ray_origin, ray_length);
}

void	calculate_intersection(t_ray *ray)
{
	calculate_intersection_point(ray);
	calculate_normal_at_intersection(ray);
}
