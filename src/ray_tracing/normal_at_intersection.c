/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_at_intersection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:52:47 by tday              #+#    #+#             */
/*   Updated: 2025/02/02 13:38:33 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

/*
	Summary
	Calculates the normal vector at a point on a sphere's surface.

	Inputs
	[t_ray*] ray: The ray containing intersection point and sphere object data.

	Outputs
	None. Updates the ray's normal_at_intersection field with a normalized
	vector perpendicular to the sphere's surface at the intersection point.

	Explanation
	The normal vector for a sphere is always the vector from the sphere's center
	to the intersection point as every point on the surface of a sphere is
	equidistant from the center.
*/
void	calculate_normal_at_sphere(t_ray *ray)
{
	ray->normal_at_intersection = vect_subtract(ray->intersection_point, \
		ray->closest_object->u_data.sphere.center);
	ray->normal_at_intersection = vect_normalise(ray->normal_at_intersection);
}

/*
	Summary
	Calculates the normal vector for a cylinder's end caps. The normal is either
	the cylinder's axis direction (for the bottom cap) or its negative (for the
	top cap).

	Inputs
	[t_ray*] ray: The ray containing intersection data and cap identifier.
	[t_Cylinder] cyl: The cylinder object containing axis information.

	Outputs
	None. Updates the ray's normal_at_intersection field with a normalized
	vector perpendicular to the cap surface. Direction depends on which cap
	was hit (cyl_closest_point == 0 for bottom, 1 for top).

	Explanation
	The normal vector for a cylinder's caps is parallel to the cylinder's axis.
	For the bottom cap (cyl_closest_point == 0), the normal points in the same
	direction as the axis. For the top cap (cyl_closest_point == 1), the normal
	points in the opposite direction. This ensures that normals always point
	outward from the cylinder's surface, which is essential for correct lighting
	and reflection calculations.
*/
void	calculate_normal_cylinder_cap(t_ray *ray, t_Cylinder cyl)
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

	Explanation
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
/*
	Summary
	Determines and calculates the appropriate normal vector for a cylinder
	based on which part of the cylinder was intersected.

	Inputs
	[t_ray*] ray: The ray containing intersection data and cylinder hit information.

	Outputs
	None. Updates the ray's normal_at_intersection field with the appropriate
	normal vector.

	Explanation
	This function acts as a dispatcher for cylinder normal calculations. It uses
	the cyl_closest_point field to determine which part of the cylinder was hit:
	- Values 0 and 1 indicate hits on the bottom and top caps respectively
	- Values 2 and 3 indicate hits on the cylinder's body
	Based on this information, it calls the appropriate specialized function to
	calculate the normal vector for that specific part of the cylinder.
*/
void	calculate_normal_at_cylinder(t_ray *ray)
{
	t_Cylinder cyl = ray->closest_object->u_data.cylinder;

	if (ray->cyl_closest_point == 0 || ray->cyl_closest_point == 1)
		calculate_normal_cylinder_cap(ray, cyl);
	else if (ray->cyl_closest_point == 2 || ray->cyl_closest_point == 3)
		calculate_normal_cylinder_body(ray, cyl);
}
/*
	Summary
	Main dispatcher function that calculates the normal vector at an intersection
	point based on the type of object that was hit.

	Inputs
	[t_ray*] ray: The ray containing intersection data and object information.

	Outputs
	None. Updates the ray's normal_at_intersection field with the appropriate
	normal vector for the intersected object.

	Explanation
	This function determines the type of object that was hit and delegates the
	normal calculation accordingly:
	- For spheres: Delegates to specialized sphere normal calculation 
		function.
	- For planes: Uses the pre-defined plane normal directly. I would have
		preferred to use a calculate_normal_at_plane function but the plane normal
		is already defined in the plane struct and norminette restricts us to 5
		functions per file.
	- For cylinders: Delegates to specialized cylinder normal calculation 
		function.
	The normal vector is essential for lighting calculations, as it determines
	how light interacts with the surface at the intersection point.
*/
void	calculate_normal_at_intersection(t_ray *ray)
{
	t_Object *closest_object = ray->closest_object;

	if (closest_object->type == SPHERE)
		calculate_normal_at_sphere(ray);
	else if (closest_object->type == PLANE)
		ray->normal_at_intersection = ray->closest_object->u_data.plane.normal;
	else if (closest_object->type == CYLINDER)
		calculate_normal_at_cylinder(ray);
}
