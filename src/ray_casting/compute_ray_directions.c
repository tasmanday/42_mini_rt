/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_ray_directions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:57:06 by tday              #+#    #+#             */
/*   Updated: 2024/08/25 17:22:03 by tday             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
t_Vector3	apply_camera_orientation(t_Vector3 ray, t_cam *camera)
{
	t_Vector3	x_axis;
	t_Vector3	y_axis;
	t_Vector3	z_axis;
	t_Vector3	orientation;
	t_Vector3	final_ray_dir;

    // Ensure camera orientation is normalized
	orientation = vect_normalise(*camera->orientation);
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
		t_mrt *mrt: The miniRT structure containing width and height of the
			screen.
		int x, int y: The pixel coordinates.
		t_cam *camera: The camera structure containing FOV and orientation.

	OUTPUTS:
		t_Vector3: The direction of the ray for the given pixel.
*/
t_Vector3	get_ray_direction(t_mrt *mrt, int x, int y, t_cam *camera)
{
	double	aspect_ratio;
	double	fov_adjustment;
	t_Vector3	ray;

	aspect_ratio = (double)mrt->width / mrt->height;
	fov_adjustment = tan((camera->fov * M_PI / 180) / 2);
	ray.x = (2 * ((double)x / mrt->width) - 1) * aspect_ratio * fov_adjustment;
	ray.y = (1 - 2 * ((double)y / mrt->height)) * fov_adjustment;
	ray.z = 1;
	ray.x *= -1; // inverts the x axis, In many 3D rendering setups, the screen space is mapped so that the left side of the image has negative x-values and the right side has positive x-values.
	ray = apply_camera_orientation(ray, camera);

	return (ray);
}

/*
    SUMMARY:
        Computes the normalised ray directions for each pixel on the screen.

    INPUTS:
        t_mrt *mrt: The miniRT structure containing width and height of the
			screen.
        t_cam *camera: The camera structure containing FOV and orientation.

    OUTPUTS:
        None.
*/
/* void	compute_ray_directions(t_mrt *mrt, t_cam *camera)
{
	int		y;
	int		x;
	t_Vector3	ray_dir;
	double	distance = 0;

	y = 0;
	while (y < mrt->height)
	{
		if (y % 100 == 0) // delete later
		{
			x = 0;
			while (x < mrt->width)
			{
				if (x % 100 == 0)
				{
					ray_dir = get_ray_direction(mrt, x, y, camera);
					// Send ray from camera coordinates in direction of ray_dir
					if (ray_intersects_sphere(camera, ray_dir, mrt->objs, &distance))
						printf("O"); // Intersection with sphere
					else
						printf("_"); // No intersection
					printf(" ");
					// calculate intersection
		//			if ((y % 500 == 0) && (x % 500 == 0))
		//				printf("Pixel [%d, %d] -> Ray direction: [%f, %f, %f]\n", x, y, ray_dir.x, ray_dir.y, ray_dir.z);
				}
				x++;
			}
			printf("\n"); // delete later
		}
		y++;
	}
} */

void	compute_ray_directions(t_mrt *mrt, t_cam *camera)
{
	int		y;
	int		x;
	t_Vector3	ray_dir;
	double	distance = 0;

	y = 0;
	while (y < mrt->height)
	{
		// Calculate the ray direction for every pixel but process every 100th row
		x = 0;
		while (x < mrt->width)
		{
//			ray_dir = get_ray_direction(mrt, x, y, camera);
			
			// Always calculate the ray direction for the center pixel
			/* if ((x == mrt->width / 2 && y == mrt->height / 2))
			{
				ray_dir = get_ray_direction(mrt, x, y, camera);
				printf("Center Ray Direction: [%f, %f, %f]\n", ray_dir.x, ray_dir.y, ray_dir.z);
				if (ray_intersects_sphere(camera, ray_dir, mrt->objs, &distance))
					printf("Center Ray intersects sphere\n");
				else
					printf("Center Ray doesn't intersect sphere\n");
			} */

			// Continue processing every 25th pixel for intersection checks
			if (y % 25 == 0 && x % 25 == 0)
			{
				ray_dir = get_ray_direction(mrt, x, y, camera);
//				printf("Ray Direction: [%f, %f, %f] ", ray_dir.x, ray_dir.y, ray_dir.z);
				if (!ray_intersects_sphere(camera, ray_dir, mrt->objs, &distance))
//					printf("O"); // Intersection with sphere
//				else
					printf("_"); // No intersection
				printf(" ");
			}

//			if ((y % 500 == 0) && (x % 500 == 0))
//				printf("Pixel [%d, %d] -> Ray direction: [%f, %f, %f]\n", x, y, ray_dir.x, ray_dir.y, ray_dir.z);
			
			x++;
		}
		if (y % 25 == 0) // Only print newline every 100th row
			printf("\n"); // delete later
		y++;
	}
}

