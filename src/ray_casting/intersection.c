/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 22:30:41 by tday              #+#    #+#             */
/*   Updated: 2025/02/01 00:15:03 by tday             ###   ########.fr       */
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
bool	ray_intersects_object(t_Scene *scene, t_ray *ray, t_Object *ignore_object)
{
	t_Object	*current_object;
	float		distance;
	bool		intersects;

	current_object = scene->objects;
	distance = INFINITY;
	ray->intersects_object = false;
	while (current_object)
	{
		if (current_object == ignore_object)
		{
			current_object = current_object->next;
			continue;
		}
		intersects = check_intersection(ray, current_object, &distance);
		if (intersects)
		{
			ray->intersects_object = true;
			if (distance < ray->closest_hit_distance)
			{ // TODO make function called update_closest_object
				ray->closest_hit_distance = distance;
				ray->closest_object = current_object;
			}
		}
		current_object = current_object->next;
	}
	return (ray->intersects_object);
}

// For a sphere, the normal is the vector from the sphere's center to the intersection point
void calculate_normal_at_sphere(t_ray *ray)
{
	ray->normal_at_intersection = vect_subtract(ray->intersection_point, ray->closest_object->u_data.sphere.center);
	ray->normal_at_intersection = vect_normalise(ray->normal_at_intersection);
}

// For a plane, the normal is constant and is the plane's normal
void calculate_normal_at_plane(t_ray *ray)
{
	ray->normal_at_intersection = ray->closest_object->u_data.plane.normal;
}

void calculate_normal_cylinder_cap(t_ray *ray, t_Cylinder cyl)
{
	ray->normal_at_intersection = vect_normalise(cyl.axis);
	if (ray->cyl_closest_point == 1)
	{
		// Reverse the normal for the opposite cap
		ray->normal_at_intersection = vect_multiply_scalar(ray->normal_at_intersection, -1);
	}
}

/*
	Summary
	Calculates the normal vector at the intersection point on the body of a cylinder.

	Inputs
	[t_ray*] ray: The ray that intersects with the cylinder.
	[t_Cylinder] cyl: The cylinder object containing its geometric properties.

	Outputs
	None. The normal vector at the intersection point is stored in the ray's
	normal_at_intersection field.

	Description
	This function computes the normal vector at the intersection point on the
	cylinder's body. It does so by:
	1. Calculating the vector from the cylinder's center to the intersection point (civ).
	2. Projecting this vector onto the cylinder's axis to find the parallel component (pc).
	3. Subtracting the parallel component from the original vector to isolate the
	   perpendicular component/normal component (nc).
	4. Normalizing the resulting vector to ensure it is a unit vector.
	imagine a right angle triangle with the hypotenuse being civ, the base being pc which runs 
	parallel to the cylinder's axis, and the perpendicular being nc.
*/
void	calculate_normal_cylinder_body(t_ray *ray, t_Cylinder cyl)
{
	t_Vector3 civ;
	float projection_length;
	t_Vector3 pc;
	t_Vector3 nc;

	civ = vect_subtract(ray->intersection_point, cyl.center);
	projection_length = vect_dot(civ, cyl.axis);
	pc = vect_multiply_scalar(cyl.axis, projection_length);
	nc = vect_subtract(civ, pc);
	ray->normal_at_intersection = vect_normalise(nc);
}

void calculate_normal_at_cylinder(t_ray *ray)
{
	t_Cylinder cyl = ray->closest_object->u_data.cylinder;

	if (ray->cyl_closest_point == 0 || ray->cyl_closest_point == 1)
		calculate_normal_cylinder_cap(ray, cyl);
	else if (ray->cyl_closest_point == 2 || ray->cyl_closest_point == 3)
		calculate_normal_cylinder_body(ray, cyl);
}

void calculate_normal_at_intersection(t_ray *ray)
{
	t_Object *closest_object = ray->closest_object;

	if (closest_object->type == SPHERE)
		calculate_normal_at_sphere(ray);
	else if (closest_object->type == PLANE)
		calculate_normal_at_plane(ray);
	else if (closest_object->type == CYLINDER)
		calculate_normal_at_cylinder(ray);
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
