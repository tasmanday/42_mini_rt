/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_ray_directions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:57:06 by tday              #+#    #+#             */
/*   Updated: 2025/02/02 14:34:26 by tday             ###   ########.fr       */
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

	Explanation
	This function handles a special case in camera orientation where the camera
	is looking directly up or down. In these cases:
	- The y component will be exactly 1 (up) or -1 (down)
	- The x and z components will be 0
	- Special handling is needed because the standard method of creating camera
	  basis vectors fails when the view direction is parallel to the up vector
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

	Explanation
	This function creates a coordinate system based on the camera's orientation
	and uses it to adjust ray directions. The process involves:

	1. Building a Coordinate System:
	   - Forward direction (Z-axis): Uses the camera's orientation directly
	   - Right direction (X-axis): Found using cross product with (0,1,0) and the
	     camera's orientation
	   - Up direction (Y-axis): Cross product of forward and right vectors
	   
	2. Special Case Handling:
	   - When the camera points straight up/down, the standard right vector
	     calculation fails
	   - In these cases, we manually set the right vector to (±1,0,0)
	   
	3. Direction Transformation:
	   - Multiplies each component of the input ray by the right, up, and forward
	     vectors (X,Y,Z axis according to the camera's orientation):
	     final.x = ray.x * right.x + ray.y * up.x + ray.z * forward.x
	     final.y = ray.x * right.y + ray.y * up.y + ray.z * forward.y
	     final.z = ray.x * right.z + ray.y * up.z + ray.z * forward.z
	   - Normalizes the result to maintain consistent ray lengths

	This ensures all rays are properly oriented relative to the camera's
	viewing direction, allowing correct rendering of the scene from any
	camera angle.
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
	t_Vector3 ray: The direction vector of the ray for the given pixel.

	Explanation
	This function converts pixel coordinates to ray directions in several steps:

	1. Screen Setup:
	   - Calculates aspect_ratio to account for non-square screens
	   - Converts FOV from degrees to radians and applies tan() to get the
	     viewport dimensions

	2. Pixel to Screen Space:
	   - Converts pixel coordinates to normalized [-1, 1] coordinates where:
	     * -1 represents the left/bottom of the screen
	     * 0 represents the center of the screen
	     * +1 represents the right/top of the screen
	   - z: Set to 1 to create initial forward direction

	3. Adjustments:
	   - Scales by FOV adjustment to implement the camera's field of view
	   - Inverts x to match conventional screen coordinate system
	   - Applies camera orientation to get final world direction

	The resulting ray direction points from the camera through the specified
	pixel on an imaginary viewport in front of the camera.
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
