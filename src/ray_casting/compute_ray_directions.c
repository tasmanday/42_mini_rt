/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_ray_directions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:57:06 by tday              #+#    #+#             */
/*   Updated: 2024/08/04 23:46:43 by tday             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
#include <math.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

/*
	SUMMARY:
		Normalizes a 3D vector, scaling it to unit length.

	INPUTS:
		t_vect v: The vector to be normalized, containing x, y, and z components.

	OUTPUTS:
		t_vect: The normalized vector with unit length.
*/
t_vect	normalise_vector(t_vect v)
{
	double	len;
	t_vect	normalised_vector;

	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (len == 0) // Add check for zero length
	{
		normalised_vector.x = 0;
		normalised_vector.y = 0;
		normalised_vector.z = 0;
	}
	else
	{
		normalised_vector.x = v.x / len;
		normalised_vector.y = v.y / len;
		normalised_vector.z = v.z / len;
	}
	return (normalised_vector);
}

/*
	SUMMARY:
		Applies the camera's orientation to a given ray direction.

	INPUTS:
		t_vect ray_dir: The initial direction of the ray.
		t_cam *camera: The camera containing orientation information.

	OUTPUTS:
		t_vect: The final ray direction after applying the camera's orientation.
*/
/* t_vect	apply_camera_orientation(t_vect ray_dir, t_cam *camera)
{
	t_vect	final_ray_dir;

	final_ray_dir.x = ray_dir.x * camera->orientation->x;
	final_ray_dir.y = ray_dir.y * camera->orientation->y;
	final_ray_dir.z = ray_dir.z * camera->orientation->z;
	final_ray_dir = normalise_vector(final_ray_dir);
	return (final_ray_dir);
} */

t_vect apply_camera_orientation(t_vect ray_dir, t_cam *camera, int x, int y)
{
    t_vect final_ray_dir;
    t_vect orientation;

    // Ensure camera orientation is normalized
    orientation = normalise_vector(*camera->orientation);

    // Apply the camera orientation as a rotation (assuming the orientation is the forward direction)
    // This is a basic approach; for more complex orientations, use a full rotation matrix
    final_ray_dir.x = ray_dir.x * orientation.x;
    final_ray_dir.y = ray_dir.y * orientation.y;
    final_ray_dir.z = ray_dir.z * orientation.z;

	if ((y % 500 == 0) && (x % 500 == 0))
	{
    	printf("Applying Camera Orientation: [%f, %f, %f] * [%f, %f, %f]\n",
           ray_dir.x, ray_dir.y, ray_dir.z,
           orientation.x, orientation.y, orientation.z);
	}
    // Normalize the final direction
    final_ray_dir = normalise_vector(final_ray_dir);

    return final_ray_dir;
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
		t_vect: The direction of the ray for the given pixel.
*/
t_vect	get_ray_direction(t_mrt *mrt, int x, int y, t_cam *camera)
{
	double	aspect_ratio;
	double	fov_adjustment;
	double	px;
	double	py;
	t_vect	ray_dir;

	aspect_ratio = (double)mrt->width / mrt->height;
	fov_adjustment = tan((camera->fov * 0.5) * M_PI / 180);
	px = (2 * ((x + 0.5) / mrt->width) - 1) * aspect_ratio * fov_adjustment;
	py = (1 - 2 * ((y + 0.5) / mrt->height)) * fov_adjustment;
	ray_dir.x = px;
	ray_dir.y = py;
	ray_dir.z = -1;
	//if ((y % 500 == 0) && (x % 500 == 0))
	//	printf("Initial Ray Direction: [%f, %f, %f]\n", ray_dir.x, ray_dir.y, ray_dir.z);
	ray_dir = normalise_vector(ray_dir);
	//if ((y % 500 == 0) && (x % 500 == 0))
	//	printf("Normalized Ray Direction: [%f, %f, %f]\n", ray_dir.x, ray_dir.y, ray_dir.z);
	ray_dir = apply_camera_orientation(ray_dir, camera, x, y);
	//if ((y % 500 == 0) && (x % 500 == 0))
	//	printf("Final Ray Direction after Orientation: [%f, %f, %f]\n", ray_dir.x, ray_dir.y, ray_dir.z);
	return (ray_dir);
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
void	compute_ray_directions(t_mrt *mrt, t_cam *camera)
{
	int		y;
	int		x;
	t_vect	ray_dir;

	y = 0;
	while (y < mrt->height)
	{
		x = 0;
		while (x < mrt->width)
		{
			ray_dir = get_ray_direction(mrt, x, y, camera);
			// Send ray from camera coordinates in direction of ray_dir
			// calculate intersection
			if ((y % 500 == 0) && (x % 500 == 0))
				printf("Pixel [%d, %d] -> Ray direction: [%f, %f, %f]\n", x, y, ray_dir.x, ray_dir.y, ray_dir.z);
			x++;
		}
		y++;
	}
}
