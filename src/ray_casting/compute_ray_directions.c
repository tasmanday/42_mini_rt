/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_ray_directions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:57:06 by tday              #+#    #+#             */
/*   Updated: 2024/12/23 00:31:04 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

/*
	Summary
	Checks if the camera orientation vector is pointing straight up or down.

	Inputs
	[t_Vector3] orientation: A vector representing the camera's orientation.

	Outputs
	[bool] Returns true if the camera is oriented straight up (y == 1) or 
	straight down (y == -1), otherwise returns false.
*/
bool	camera_pointed_straight_up_or_down(t_Vector3 orientation)
{
	if (orientation.y == 1 || orientation.y == -1)
		return (true);
	else
		return (false);
}

/*
	SUMMARY:
		Applies the camera's orientation to a given ray direction.

	INPUTS:
		t_Vector3 ray_dir: The initial direction of the ray.
		t_cam *camera: The camera containing orientation information.

	OUTPUTS:
		t_Vector3: The final ray direction after applying the camera's orientation.
*/
t_Vector3	apply_camera_orientation(t_Vector3 ray, t_Scene *scene)
{
	t_Vector3	x_axis;
	t_Vector3	y_axis;
	t_Vector3	z_axis;
	t_Vector3	orientation;
	t_Vector3	final_ray_dir;

    // Ensure camera orientation is normalized
	orientation = vect_normalise(scene->camera.orientation);
	z_axis = orientation;
	if (camera_pointed_straight_up_or_down(orientation))
	{
		if (orientation.y == 1)
			x_axis = vector(1, 0, 0);
		else
			x_axis = vector(-1, 0, 0);
	}
	else
		x_axis = vect_cross(vector(0, 1, 0), z_axis);
	y_axis = vect_cross(z_axis, x_axis);
	final_ray_dir.x = ray.x * x_axis.x + ray.y * y_axis.x + ray.z * z_axis.x;
	final_ray_dir.y = ray.x * x_axis.y + ray.y * y_axis.y + ray.z * z_axis.y;
	final_ray_dir.z = ray.x * x_axis.z + ray.y * y_axis.z + ray.z * z_axis.z;

    // Normalize the final direction
	final_ray_dir = vect_normalise(final_ray_dir);

	return (final_ray_dir);
}

/*
	SUMMARY:
		Calculates the ray direction for a given pixel on the screen.

	INPUTS:
		t_Scene *scene: The miniRT structure containing width and height of the
			screen.
		int x, int y: The pixel coordinates.

	OUTPUTS:
		t_Vector3 ray: The direction of the ray for the given pixel.
*/
t_Vector3	get_ray_direction(t_Scene *scene, int x, int y)
{
	float	aspect_ratio;
	float	fov_adjustment;
	t_Vector3	ray;

//	printf("in grd\n"); // TODO remove
	aspect_ratio = (float)scene->mlx.width / scene->mlx.height;
	fov_adjustment = tan((scene->camera.fov * M_PI / 180) / 2);
	ray.x = (2 * ((float)x / scene->mlx.width) - 1) * aspect_ratio * fov_adjustment;
	ray.y = (1 - 2 * ((float)y / scene->mlx.height)) * fov_adjustment;
	ray.z = -1; // makes the camera look into the screen by default
	ray.x *= -1; // inverts the x axis, In many 3D rendering setups, the screen space is mapped so that the left side of the image has negative x-values and the right side has positive x-values.
	ray = apply_camera_orientation(ray, scene);

	return (ray);
}

void	init_ray(t_Scene *scene, t_ray *ray, int x, int y)
{
	ray->ray_origin = scene->camera.position;
	ray->ray_dir = get_ray_direction(scene, x, y);
	ray->intersects_object = false;
	ray->closest_intersection = INFINITY;
	ray->closest_object = NULL;
	ray->colour.r = 0;
	ray->colour.g = 0;
	ray->colour.b = 0;
}

void	check_object_intersection(t_Scene *scene, t_ray *ray)
{
	t_Object	*current_object;
	float		distance;

	current_object = scene->objects;
	distance = INFINITY;
	while (current_object)
	{
		if (current_object->type == PLANE)
			if (ray_intersects_plane(ray, \
					current_object->u_data.plane.point, \
					current_object->u_data.plane.normal, &distance))
				ray->intersects_object = true;
		if (current_object->type == SPHERE)
			if (ray_intersects_sphere(ray, \
					current_object->u_data.sphere, &distance))
				ray->intersects_object = true;
		if (current_object->type == CYLINDER)
			if (ray_intersects_cylinder(ray, \
					current_object->u_data.cylinder, &distance))
				ray->intersects_object = true;
		if (distance < ray->closest_intersection)
		{
			ray->closest_intersection = distance;
			ray->closest_object = current_object;
		}
		current_object = current_object->next;
	}
	if (ray->intersects_object)
	{
		if (ray->closest_object->type == SPHERE)
			ray->colour = ray->closest_object->u_data.sphere.colour;
		else if (ray->closest_object->type == PLANE)
			ray->colour = ray->closest_object->u_data.plane.colour;
		else if (ray->closest_object->type == CYLINDER)
			ray->colour = ray->closest_object->u_data.cylinder.colour;
	}
}

/*
    SUMMARY:
        Computes the normalised ray directions for each pixel on the screen.

    INPUTS:
        t_Scene *scene: The miniRT structure containing width and height of the
			screen.

    OUTPUTS:
        None.
*/
/*void	compute_ray_directions(t_Scene *scene) // rename to ray_trace()
{
	int		y;
	int		x;
	t_ray	ray;

	y = 0;
	while (y < scene->mlx.height)
	{
		x = 0;
		while (x < scene->mlx.width)
		{
			// process every 25th pixel for intersection checks, this will be every pixel on the real thing
			if (y % 25 == 0 && x % 25 == 0)
			{
				init_ray(scene, &ray, x, y);
				check_object_intersection(scene, &ray);

				if (!ray->intersects_object)
					my_mlx_pixel_put(x, y, BLACK);
				else
					my_mlx_pixel_put(x, y, get_pixel_colour());

//				ray_intersects_sphere(scene, ray_dir, &distance);

//				ray_intersects_plane(scene, ray_dir, &distance);
			}
			x++;
		}
		if (y % 25 == 0) // Only print newline every 100th row
			printf("\n"); // delete later
		y++;
	}
	printf("\n");
	y = scene->mlx.height / 2;
	x = scene->mlx.width / 2;
	ray_dir = get_ray_direction(scene, x, y);
	ray_intersects_plane(scene, ray_dir, &distance);
	printf("ray_dir: %f, %f, %f\n", ray_dir.x, ray_dir.y, ray_dir.z);
	printf("distance: %f\n", distance); 
} */
