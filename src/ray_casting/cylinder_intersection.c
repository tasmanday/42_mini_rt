/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:49:10 by tday              #+#    #+#             */
/*   Updated: 2025/01/06 20:49:39 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

/*
	Summary
	Checks if the contact point is within the height of the cylinder.

	Inputs
	[t_ray*] ray: The ray being checked for intersection.
	[t_Cylinder] cyl: The cylinder to check against.
	[float] t: The distance along the ray to the contact point.

	Outputs
	[bool] Returns true if the contact point is within the cylinder's height,
		false otherwise.
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
	[float distance[4]]: Array to store the intersection distances.

	Outputs
	None. The intersection distances are stored in the array distance.
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
	[float distance[4]]: Array to store the intersection distances.

	Outputs
	None. The intersection distances are stored in the array distance.
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
