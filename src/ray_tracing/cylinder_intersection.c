/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:49:10 by tday              #+#    #+#             */
/*   Updated: 2025/04/10 01:10:32 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

/*
	Summary
	Determines if a ray-cylinder intersection point lies within the cylinder's
	height bounds.

	Inputs
	[t_ray*] ray: The ray being checked.
	[t_Cylinder] cyl: The cylinder to check against.
	[float] t: The distance along the ray to the intersection point.

	Outputs
	[bool] Returns true if the point lies between the cylinder's end caps,
	false otherwise.

	Explanation
	This function checks height validity in three steps:
	1. Calculates the actual intersection point using the ray equation
	2. Projects the vector from cylinder center to intersection point onto
	   the cylinder's axis using dot product
	3. Checks if this projected height falls within ±height/2 of the center

	This ensures we only count intersections that hit the finite cylinder,
	not its infinite extension.
*/
bool	contact_point_within_cylinder_height(t_ray *ray, t_Cylinder cyl, \
		float t)
{
	t_Vector3	contact_point;
	float		contact_height;

	contact_point = vect_add(ray->ray_origin, \
		vect_multiply_scalar(ray->ray_dir, t));
	contact_height = vect_dot(vect_subtract(contact_point, cyl.center), \
		cyl.axis);
	if (fabs(contact_height) <= cyl.height / 2)
		return (true);
	return (false);
}

/*
	Summary
	Calculates the distances at which a ray intersects the infinite cylinder.

	Inputs
	[t_ray*] ray: The ray being checked for intersection.
	[t_Cylinder] cyl: The cylinder to check against.
	[float t[2]]: Array to store the intersection distances.

	Outputs
	None. The intersection distances are stored in the array t.

	Explanation
	This function finds intersection points using these steps:
	1. Calculate Orthogonal Components:
	   - rd_ax_orthog: Cross product of ray direction and cylinder axis
	   - ro_cen_ax_orthog: Cross product of ray-to-center vector and axis
	   These vectors represent the perpendicular components needed for
	   intersection calculation

	2. Build Quadratic Equation (at² + bt + c = 0):
	   - a = dot(rd_ax_orthog, rd_ax_orthog)
	   - b = 2 * dot(rd_ax_orthog, ro_cen_ax_orthog)
	   - c = dot(ro_cen_ax_orthog, ro_cen_ax_orthog) - radius²

	3. Solve Using Quadratic Formula:
	   - If discriminant ≥ 0: Two solutions (ray hits cylinder)
	   - If discriminant < 0: No solutions (ray misses cylinder)
*/
void	calculate_contact_distances(t_ray *ray, t_Cylinder cyl, float t[2])
{
	t_Vector3	rd_ax_orthog;
	t_Vector3	ro_cen_ax_orthog;
	t_Quad		q;
	float		discriminant;

	rd_ax_orthog = vect_cross(ray->ray_dir, cyl.axis);
	ro_cen_ax_orthog = vect_cross(vect_subtract(ray->ray_origin, cyl.center), \
		cyl.axis);
	q.a = vect_dot(rd_ax_orthog, rd_ax_orthog);
	q.b = 2 * vect_dot(rd_ax_orthog, ro_cen_ax_orthog);
	q.c = vect_dot(ro_cen_ax_orthog, ro_cen_ax_orthog) - \
		pow(cyl.diameter / 2, 2);
	discriminant = q.b * q.b - 4 * q.a * q.c;
	if (discriminant >= 0)
	{
		t[0] = (-q.b - sqrt(discriminant)) / (2 * q.a);
		t[1] = (-q.b + sqrt(discriminant)) / (2 * q.a);
	}
	else
	{
		t[0] = -1;
		t[1] = -1;
	}
}

/*
	Summary
	Checks for intersections between the ray and the cylindrical body.

	Inputs
	[t_ray*] ray: The ray being checked for intersection.
	[t_Cylinder] cyl: The cylinder to check against.
	[float distance[4]]: Array to store intersection distances, where indices
		2 and 3 are used for cylinder body hits.

	Outputs
	None. Updates the distance array with valid intersection distances.

	Explanation
	This function processes cylinder body intersections in two steps:
	1. Gets potential intersection distances with the infinite cylinder
	2. For each positive distance, checks if the intersection point lies
	   within the cylinder's height bounds

	Only valid intersections (positive distance and within height) are stored
	in the distance array at indices 2 and 3 (0 and 1 are reserved for caps).
*/
void	check_cylinder_body(t_ray *ray, t_Cylinder cyl, float distance[4])
{
	float	t[2];

	calculate_contact_distances(ray, cyl, t);
	if (t[0] > 0 && contact_point_within_cylinder_height(ray, cyl, t[0]))
		distance[2] = t[0];
	if (t[1] > 0 && contact_point_within_cylinder_height(ray, cyl, t[1]))
		distance[3] = t[1];
}

/*
	Summary
	Checks if a contact point is within the radius of a cylinder's end cap.

	Inputs
	[t_Vector3] contact_point: The point to check.
	[t_Vector3] cap_center: The center of the cap.
	[float] radius: The radius of the cap.

	Outputs
	[bool] Returns true if the contact point is within the cap's radius,
		false otherwise.

	Explanation
	This function uses the dot product with itself to calculate distance²:
	1. Finds vector from cap center to contact point
	2. Compares dot(diff, diff) with radius²
	3. If distance² ≤ radius², point is within or on the cap

	Using dot product with itself avoids the need for a square root operation,
	making this check more efficient than using actual distance.
*/
bool	within_radius(t_Vector3 contact_point, t_Vector3 cap_center, \
		float radius)
{
	t_Vector3	diff;

	diff = vect_subtract(contact_point, cap_center);
	if (vect_dot(diff, diff) <= radius * radius)
		return (true);
	return (false);
}

/*
	Summary
	Checks for intersections between the ray and the cylinder's end caps.

	Inputs
	[t_ray*] ray: The ray being checked for intersection.
	[t_Cylinder] cyl: The cylinder to check against.
	[float distance[4]]: Array to store intersection distances, where indices
		0 and 1 are used for cap hits.

	Outputs
	None. Updates the distance array with valid cap intersection distances.

	Explanation
	This function checks both end caps in three steps:
	1. Calculate Cap Centers:
	   - Uses cylinder axis and height to find centers of both caps
	   - cap_a = center + (axis * height/2)
	   - cap_b = center - (axis * height/2)

	2. For Each Cap:
	   - Check if ray intersects cap's plane
	   - If yes, calculate exact intersection point

	3. Validate Intersections:
	   - Ensure intersection point lies within cap's radius
	   - Store valid distances in array (index 0 for cap_a, 1 for cap_b)
*/
void	check_end_cap(t_ray *ray, t_Cylinder cyl, float distance[4])
{
	t_Vector3	offset;
	t_Vector3	cap_a_center;
	t_Vector3	cap_b_center;
	float		t;
	t_Vector3	contact_point;

	offset = vect_multiply_scalar(cyl.axis, cyl.height / 2.0f);
	cap_a_center = vect_add(cyl.center, offset);
	cap_b_center = vect_subtract(cyl.center, offset);
	if (ray_intersects_plane(ray, cap_a_center, cyl.axis, &t) && t > 0)
	{
		contact_point = vect_add(ray->ray_origin, \
			vect_multiply_scalar(ray->ray_dir, t));
		if (within_radius(contact_point, cap_a_center, cyl.diameter / 2))
			distance[0] = t;
	}
	if (ray_intersects_plane(ray, cap_b_center, cyl.axis, &t) && t > 0)
	{
		contact_point = vect_add(ray->ray_origin, \
			vect_multiply_scalar(ray->ray_dir, t));
		if (within_radius(contact_point, cap_b_center, cyl.diameter / 2))
			distance[1] = t;
	}
}

/*
	Summary
	Determines if a ray intersects with a cylinder and finds the closest
	intersection point.

	Inputs
	[t_ray*] ray: The ray being checked for intersection.
	[t_Cylinder] cyl: The cylinder to check against.
	[float*] distance: Pointer to store the closest intersection distance.

	Outputs
	[bool] Returns true if there is an intersection, false otherwise.
	Also updates distance and ray->cyl_closest_point for the closest hit.

	Explanation
	This function coordinates the complete cylinder intersection test:
	1. Initialization:
	   - Normalizes cylinder axis
	   - Creates array for up to 4 intersection points (2 caps, 2 body)
	   
	2. Intersection Tests:
	   - Checks end caps (points[0] and points[1])
	   - Checks cylinder body (points[2] and points[3])
	   
	3. Find Closest Hit:
	   - Examines all valid intersection points (distance > 0)
	   - Updates distance if closer hit is found
	   - Records which part was hit (caps or body) in cyl_closest_point
*/
bool	ray_intersects_cylinder(t_ray *ray, t_Cylinder cyl, float *distance)
{
	float	points[4];
	bool	intersection_flag;
	int		i;

	cyl.axis = vect_normalise(cyl.axis);
	points[0] = -1;
	points[1] = -1;
	points[2] = -1;
	points[3] = -1;
	intersection_flag = false;
	check_end_cap(ray, cyl, points);
	check_cylinder_body(ray, cyl, points);
	i = 0;
	while (i < 4)
	{
		if (points[i] > 0 && points[i] < *distance)
		{
			*distance = points[i];
			intersection_flag = true;
			ray->cyl_closest_point = i;
		}
		i++;
	}
	return (intersection_flag);
}
