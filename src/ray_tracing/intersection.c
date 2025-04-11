/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 22:30:41 by tday              #+#    #+#             */
/*   Updated: 2025/04/11 22:10:53 by tday             ###   ########.fr       */
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

	Explanation
	Dispatches to the appropriate intersection test function based on the
	object type (plane, sphere, or cylinder).
*/
bool	check_intersection(t_ray *ray, t_Object *object, float *distance)
{
	if (object->type == PLANE)
		return (ray_intersects_plane(ray, object->u_data.plane.point, \
			object->u_data.plane.normal, distance));
	else if (object->type == SPHERE)
		return (ray_intersects_sphere(ray, object->u_data.sphere, distance));
	else if (object->type == CYLINDER)
		return (ray_intersects_cyl(ray, object->u_data.cylinder, \
			distance));
	return (false);
}

/*
	Summary
	Updates the ray's closest intersection data when a closer object intersection
	is found during ray tracing.

	Inputs
	[t_ray*] ray: The ray to update.
	[t_Object*] object: The object that was intersected.
	[float] distance: The distance to the intersection point.

	Outputs
	None. Updates the ray's closest_hit_distance and closest_object fields.
*/
void	update_closest_object(t_ray *ray, t_Object *object, float distance)
{
	ray->closest_hit_distance = distance;
	ray->closest_object = object;
}

/*
	Summary
	Checks for intersections between a ray and all objects in the scene. When
	calculating shadows, the object casting the shadow is passed as ignore_obj
	to prevent self-shadowing artifacts.

	Inputs
	[t_Scene*] scene: The scene containing the list of objects.
	[t_ray*] ray: The ray to check for intersections.
	[t_Object*] ignore_obj: Object to ignore during intersection tests (typically
	                        the object being checked for shadows to prevent
	                        self-shadowing). Can be NULL for primary rays.

	Outputs
	[bool] Returns true if the ray intersects with any object, false otherwise.
	Also updates the ray's intersection properties based on the closest hit.

	Explanation
	This function processes intersections in several steps:

	1. Initialization:
	   - Sets initial distance to infinity
	   - Marks ray as not intersecting any object yet

	2. Scene Traversal:
	   - Iterates through all objects in the scene
	   - Skips the ignored object (important for shadow calculations)
	   - Tests each object for intersection

	3. Intersection Handling:
	   - Updates ray status when any intersection is found
	   - Keeps track of the closest intersection point
	   - Updates object reference and distance for closest object
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
			continue ;
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

/*
	Summary
	Calculates the 3D point where a ray intersects with an object using the
	formula: intersection_point = origin + direction * distance.

	Inputs
	[t_ray*] ray: The ray containing origin, direction, and closest hit distance.

	Outputs
	None. Updates the ray's intersection_point field with the calculated point
	in 3D space.

	Explanation
	This function finds the exact point of intersection by:
	1. Scaling the ray direction by the hit distance to get the offset
	2. Adding this offset to the ray origin to get the intersection point
*/
void	calculate_intersection_point(t_ray *ray)
{
	t_Vector3	ray_length;

	ray_length = vect_multiply_scalar(ray->ray_dir, ray->closest_hit_distance);
	ray->intersection_point = vect_add(ray->ray_origin, ray_length);
}

/*
	Summary
	Calculates all intersection-related properties for a ray that has hit an
	object. This includes both the intersection point in 3D space and the
	surface normal at that point.

	Inputs
	[t_ray*] ray: The ray that has intersected with an object.

	Outputs
	None. Updates the ray's intersection_point and normal fields.
*/
void	calculate_intersection(t_ray *ray)
{
	calculate_intersection_point(ray);
	calculate_normal_at_intersection(ray);
}
