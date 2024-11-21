/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:49:10 by tday              #+#    #+#             */
/*   Updated: 2024/11/21 23:45:15 by tday             ###   ########.fr       */
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

	// cap b
	t_Vector3 cap_b_center = vect_subtract(cylinder.center, offset);
	if (ray_intersects_plane(ray, cap_b_center, cylinder.axis, &temp_distance) \
	&& intersection_within_radius(ray, cylinder, cap_a_center, temp_distance) \
	&& temp_distance < *distance)
	{
		*distance = temp_distance;
	}

	return (distance);
}

float	get_quadratic_discriminant(t_ray *ray, t_Cylinder cyl, t_Vector3 dp, float *a)
{
	float	b;
	float	c;
	float	dot_dir_axis;
	float	dot_dp_axis;

	dot_dir_axis = vect_dot(ray->ray_dir, cyl.axis);
	dot_dp_axis = vect_dot(dp, cyl.axis);
	*a = vect_dot(ray->ray_dir, ray->ray_dir) - pow(dot_dir_axis, 2);
	b = 2 * (vect_dot(ray->ray_dir, dp) - dot_dir_axis * dot_dp_axis);
	c = vect_dot(dp, dp) - pow(dot_dp_axis, 2) - pow(cyl.diameter / 2, 2);
	return (b * b - 4 * *a * c);
}

bool	is_valid_intersection(t_Vector3 point, t_Cylinder cyl)
{
	float		dot;
	t_Vector3	v;
	float		h;

	v = vect_subtract(point, cyl.center);
	dot = vect_dot(v, cyl.axis);
	h = cyl.height / 2;
	return (fabs(dot) <= h);
}

float	*check_cylinder_body_intersection(t_ray *ray, t_Cylinder cyl, float *distance)
{
	float		a;
	float		discriminant;
	float		t1;
	float		t2;
	t_Vector3	dp;

	dp = vect_subtract(ray->ray_origin, cyl.center);
	discriminant = get_quadratic_discriminant(ray, cyl, dp, &a);
	if (discriminant < 0)
		return (distance);
	t1 = (-sqrt(discriminant)) / (2 * a);
	t2 = (sqrt(discriminant)) / (2 * a);
	if (t1 > 0 && t1 < *distance && \
		is_valid_intersection(vect_add(ray->ray_origin, \
		vect_multiply_scalar(ray->ray_dir, t1)), cyl))
		*distance = t1;
	if (t2 > 0 && t2 < *distance && \
		is_valid_intersection(vect_add(ray->ray_origin, \
		vect_multiply_scalar(ray->ray_dir, t2)), cyl))
		*distance = t2;
	return (distance);
}

bool	ray_intersects_cylinder(t_Scene *scene, t_Vector3 ray_dir, float *distance)
{
	t_ray	ray;
	float	orig_dist;

	orig_dist = *distance;
	ray.ray_origin = scene->camera.position;
	ray.ray_dir = ray_dir;
	check_end_plane_intersection(&ray, scene->objects->u_data.cylinder, \
		distance);
	check_cylinder_body_intersection(&ray, scene->objects->u_data.cylinder, \
		distance);
	return (*distance < orig_dist);
}
