/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_ray_directions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:57:06 by tday              #+#    #+#             */
/*   Updated: 2025/02/01 00:15:04 by tday             ###   ########.fr       */
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
	Summary
	Applies the camera's orientation to a given ray direction.

	Inputs
	t_Vector3 ray_dir: The initial direction of the ray.
	t_cam *camera: The camera containing orientation information.

	Outputs
	t_Vector3: The final ray direction after applying the camera's
	orientation.
*/
t_Vector3	apply_camera_orientation(t_Vector3 ray, t_Scene *scene)
{
	t_Vector3	x_axis;
	t_Vector3	y_axis;
	t_Vector3	z_axis;
	t_Vector3	orientation;
	t_Vector3	final_ray_dir;

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
	final_ray_dir = vect_normalise(final_ray_dir);

	return (final_ray_dir);
}

/*
	Summary
		Calculates the ray direction for a given pixel on the screen.

	Inputs
	t_Scene *scene: The miniRT structure containing width and height of the
		screen.
	int x, int y: The pixel coordinates.

	Outputs
	t_Vector3 ray: The direction of the ray for the given pixel.

	Notes
	ray.x *= -1; This line inverts the x axis, In many 3D rendering setups, the
	screen space is mapped so that the left side of the image has negative
	x-values and the right side has positive x-values.
*/
t_Vector3	get_ray_direction(t_Scene *scene, int x, int y)
{
	float		aspect_ratio;
	float		fov_adjustment;
	t_Vector3	ray;

	aspect_ratio = (float)scene->mlx.width / scene->mlx.height;
	fov_adjustment = tan((scene->camera.fov * M_PI / 180) / 2);
	ray.x = (2 * ((float)x / scene->mlx.width) - 1) * aspect_ratio * \
		fov_adjustment;
	ray.y = (1 - 2 * ((float)y / scene->mlx.height)) * fov_adjustment;
	ray.z = 1;
	ray.x *= -1;
	ray = apply_camera_orientation(ray, scene);

	return (ray);
}
