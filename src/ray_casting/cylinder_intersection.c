/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:49:10 by tday              #+#    #+#             */
/*   Updated: 2024/12/24 13:32:19 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

/*
bool	intersection_within_radius(t_ray *ray, t_Cylinder cylinder, t_Vector3 cap_center, float temp_distance)
{
	if (vect_distance(vect_add(ray->ray_origin, \
	vect_multiply_scalar(ray->ray_dir, temp_distance)), cap_center) \
	<= cylinder.diameter / 2)
		return (true);
	return (false);
}

bool	check_end_plane_intersection(t_ray *ray, t_Cylinder cylinder, float *distance)
{
//	printf("check_end_plane_intersection called\n"); // TODO remove
	t_Vector3	offset;
	t_Vector3	cap_a_center;
	t_Vector3	cap_b_center;
	float		temp_distance;
	bool		intersection_flag;

	intersection_flag = false;
	// Scale the normalised axis by half the height to get the offset
	offset = vect_multiply_scalar(cylinder.axis, cylinder.height / 2.0f);

	// cap a
	cap_a_center = vect_add(cylinder.center, offset);
//	if (ray_intersects_plane(ray, cap_a_center, cylinder.axis, &temp_distance) && intersection_within_radius(ray, cylinder, cap_a_center, temp_distance))	// TODO restore

	if (ray_intersects_plane(ray, cap_a_center, cylinder.axis, &temp_distance)) // TODO remove
	{
	//	printf("%f\n", temp_distance); // TODO remove
	//	printf("ray intersects cylinder cap a plane\n"); // TODO remove
		if (intersection_within_radius(ray, cylinder, cap_a_center, temp_distance)) // TODO remove
		{
			printf("ray intersects cylinder cap a within radius\n"); // TODO remove
			*distance = temp_distance;
			intersection_flag = true;
		}
	}

	// cap b
	cap_b_center = vect_subtract(cylinder.center, offset);
//	if (ray_intersects_plane(ray, cap_b_center, cylinder.axis, &temp_distance) && intersection_within_radius(ray, cylinder, cap_a_center, temp_distance) && temp_distance < *distance) 	// TODO restore

	if (ray_intersects_plane(ray, cap_b_center, vect_multiply_scalar(cylinder.axis, -1), &temp_distance)) // TODO remove
	{
	//	printf("ray intersects cylinder cap b plane\n"); // TODO remove
		if (intersection_within_radius(ray, cylinder, cap_b_center, temp_distance) \
		&& temp_distance < *distance) // TODO remove
		{
			printf("ray intersects cylinder cap b within radius\n"); // TODO remove
			*distance = temp_distance;
			intersection_flag = true;
		}
	}

	return (intersection_flag);
}

bool	ray_intersects_cylinder(t_ray *ray, t_Cylinder cylinder, float *distance)
{
	if (check_end_plane_intersection(ray, cylinder, distance))
		return (printf("ray intersects cylinder caps\n"), true);
	return (false);
}
*/




/*float	get_quadratic_discriminant(t_ray *ray, t_Cylinder cyl, t_Vector3 dp, float *a)
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
} */




float calculate_t_for_cap(t_ray *ray, t_Vector3 cap_center, t_Vector3 axis)
{
    float numerator;
    float denominator;

	numerator = vect_dot(axis, vect_subtract(ray->ray_origin, cap_center));
	denominator = vect_dot(axis, ray->ray_dir);
    if (fabs(denominator) < 1e-6) // Check for parallelism
        return (-1); // No intersection
    return (numerator / denominator);
}

bool	intersection_within_radius(t_Vector3 intersection_point, t_Vector3 cap_center, float radius) // **** this is the issue, distance squared is way bigger than radius squared ****
{
	t_Vector3	diff;
	float		distance_squared;
	float		radius_squared;

    diff = vect_subtract(intersection_point, cap_center);
    distance_squared = vect_dot(diff, diff);
	radius_squared = radius * radius;
	printf("distance_squared = %f, radius_squared = %f\n", distance_squared, radius_squared); // TODO remove
	if (distance_squared < radius_squared)
		return (printf("intersection_within_radius true\n"), true);
	return (false);
}

void	check_end_cap_intersection(t_ray *ray, t_Cylinder cylinder, float intersections[4])
{
	t_Vector3	offset;
	t_Vector3	cap_a_center;
	t_Vector3	cap_b_center;
	float		t[2];
	t_Vector3	intersection_point;

	offset = vect_multiply_scalar(cylinder.axis, cylinder.height / 2.0f);
	cap_a_center = vect_add(cylinder.center, offset);
	cap_b_center = vect_subtract(cylinder.center, offset);

	t[0] = calculate_t_for_cap(ray, cap_a_center, cylinder.axis);
	t[1] = calculate_t_for_cap(ray, cap_b_center, cylinder.axis);
//	printf("t[0] = %f\n", t[0]); // TODO remove
//	printf("t[1] = %f\n", t[1]); // TODO remove

	if (t[0] > 0)
	{
//		printf("t[0] = %f\n", t[0]); // TODO remove
		intersection_point = vect_add(ray->ray_origin, vect_multiply_scalar(ray->ray_dir, t[0]));
		if (intersection_within_radius(intersection_point, cap_a_center, cylinder.diameter / 2) || true)
			intersections[0] = t[0];
	}
	if (t[1] > 0)
	{
//		printf("t[1] = %f\n", t[1]); // TODO remove
		intersection_point = vect_add(ray->ray_origin, vect_multiply_scalar(ray->ray_dir, t[1]));
		if (intersection_within_radius(intersection_point, cap_b_center, cylinder.diameter / 2) || true)
			intersections[1] = t[1];
	}
}

float	min_positive(float *array)
{
	float	min;
	int		i;

	min = INFINITY;
	i = 0;
	while (i < 4)
	{
		if (array[i] > 0 && array[i] < min)
			min = array[i];
		i++;
	}
	return (min);
}

bool	ray_intersects_cylinder(t_ray *ray, t_Cylinder cylinder, float *distance)
{
	float	intersections[4] = {-1, -1, -1, -1};
	int		i;
	bool	intersection_flag;

//	printf("ray_intersects_cylinder called\n"); // TODO remove

	i = 0;
	intersection_flag = false;
/*	while (i < 4)
	{
		*intersections[i] = -1;
		i++;
	} */

	check_end_cap_intersection(ray, cylinder, intersections);
//	printf("intersections[0] = %f\n", intersections[0]); // TODO remove
//	printf("intersections[1] = %f\n", intersections[1]); // TODO remove

	while (i < 4)
	{
		if (intersections[i] > 0 && intersections[i] < *distance)
		{
			*distance = intersections[i];
			intersection_flag = true;
		}
		i++;
	}
	if (intersection_flag)
	{
		printf("distance = %f\n", *distance); // TODO remove
		return (printf("ray intersects cylinder caps\n"), true);
	}
	return (false);
}
