/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_ray_directions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:57:06 by tday              #+#    #+#             */
/*   Updated: 2025/01/05 23:49:29 by tday             ###   ########.fr       */
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

/*
	Summary
	Initializes a ray with its origin, direction, and default intersection
	properties.

	Inputs
	[t_Scene*] scene: The scene containing the camera position.
	[t_ray*] ray: The ray to initialize.
	[int] x: The x-coordinate of the pixel.
	[int] y: The y-coordinate of the pixel.

	Outputs
	None. The ray is initialized with its origin, direction, and default
	properties.
*/
void	init_ray(t_Scene *scene, t_ray *ray, int x, int y)
{
	ray->ray_origin = scene->camera.position;
	ray->ray_dir = get_ray_direction(scene, x, y);
	ray->intersects_object = false;
	ray->closest_hit_distance = INFINITY;
	ray->closest_object = NULL;
	ray->colour.r = 0;
	ray->colour.g = 0;
	ray->colour.b = 0;
}

/*
	Summary
	Sets the color of a ray based on the type of the closest intersected object.

	Inputs
	[t_ray*] ray: The ray whose color is to be set.

	Outputs
	None. The color is set in the ray structure.
*/
void	set_ray_colour(t_ray *ray)
{
	if (ray->closest_object->type == SPHERE)
		ray->colour = ray->closest_object->u_data.sphere.colour;
	else if (ray->closest_object->type == PLANE)
		ray->colour = ray->closest_object->u_data.plane.colour;
	else if (ray->closest_object->type == CYLINDER)
		ray->colour = ray->closest_object->u_data.cylinder.colour;
}

/*
	Summary
	Checks if a ray intersects with a given object and updates the intersection
	distance.

	Inputs
	[t_ray*] ray: The ray to check for intersection.
	[t_Object*] object: The object to check against.
	[float*] distance: Pointer to store the intersection distance.

	Outputs
	[bool] Returns true if there is an intersection, false otherwise.
*/
bool	check_intersection(t_ray *ray, t_Object *object, float *distance)
{
	if (object->type == PLANE)
		return (ray_intersects_plane(ray, object->u_data.plane.point, \
			object->u_data.plane.normal, distance));
	else if (object->type == SPHERE)
		return (ray_intersects_sphere(ray, object->u_data.sphere, distance));
	else if (object->type == CYLINDER)
		return (ray_intersects_cylinder(ray, object->u_data.cylinder, \
			distance));
	return (false);
}

void calculate_normal(t_ray *ray)
{
	t_Vector3 intersection_point;
	t_Object *closest_object = ray->closest_object;

	// Calculate the intersection point
	intersection_point = vect_add(ray->ray_origin, vect_multiply_scalar(ray->ray_dir, ray->closest_hit_distance));

	if (closest_object->type == SPHERE)
	{
		// For a sphere, the normal is the vector from the sphere's center to the intersection point
		ray->normal_at_intersection = vect_subtract(intersection_point, closest_object->u_data.sphere.center);
		ray->normal_at_intersection = vect_normalise(ray->normal_at_intersection);
	}
	else if (closest_object->type == PLANE)
	{
		// For a plane, the normal is constant and is the plane's normal
		ray->normal_at_intersection = closest_object->u_data.plane.normal;
	}
	else if (closest_object->type == CYLINDER)
	{
		t_Cylinder cyl = closest_object->u_data.cylinder;

		if (ray->cyl_closest_point == 0 || ray->cyl_closest_point == 1)
		{
			// Intersection is on an end cap
			ray->normal_at_intersection = vect_normalise(cyl.axis);
			if (ray->cyl_closest_point == 1)
			{
				// Reverse the normal for the opposite cap
				ray->normal_at_intersection = vect_multiply_scalar(ray->normal_at_intersection, -1);
			}
		}
		else if (ray->cyl_closest_point == 2 || ray->cyl_closest_point == 3)
		{
			// Intersection is on the cylindrical body
			t_Vector3 to_point = vect_subtract(intersection_point, cyl.center);
			float projection_length = vect_dot(to_point, cyl.axis);
			t_Vector3 projection = vect_multiply_scalar(cyl.axis, projection_length);
			ray->normal_at_intersection = vect_subtract(to_point, projection);
			ray->normal_at_intersection = vect_normalise(ray->normal_at_intersection);
		}
	}
}

void calculate_lighting(t_Scene *scene, t_ray *ray)
{
	t_Vector3	light_dir;
	float		intensity;

	light_dir = vect_normalise(vect_subtract(scene->light.position, vect_multiply_scalar(ray->ray_dir, ray->closest_hit_distance)));
	intensity = vect_dot(light_dir, ray->normal_at_intersection);
	if (intensity < 0)
		intensity = 0;
	if (ray->closest_object->type == SPHERE)
		{
			ray->colour.r = fmin(ray->closest_object->u_data.sphere.colour.r * intensity, 1);
			ray->colour.g = fmin(ray->closest_object->u_data.sphere.colour.g * intensity, 1);
			ray->colour.b = fmin(ray->closest_object->u_data.sphere.colour.b * intensity, 1);
		}
	else if (ray->closest_object->type == PLANE)
		{
			ray->colour.r = fmin(ray->closest_object->u_data.plane.colour.r * intensity, 1);
			ray->colour.g = fmin(ray->closest_object->u_data.plane.colour.g * intensity, 1);
			ray->colour.b = fmin(ray->closest_object->u_data.plane.colour.b * intensity, 1);
		}
	else if (ray->closest_object->type == CYLINDER)
		{
			ray->colour.r = fmin(ray->closest_object->u_data.cylinder.colour.r * intensity, 1);
			ray->colour.g = fmin(ray->closest_object->u_data.cylinder.colour.g * intensity, 1);
			ray->colour.b = fmin(ray->closest_object->u_data.cylinder.colour.b * intensity, 1);
		}
}

/*
	Summary
	Checks for intersections between a ray and all objects in the scene.

	Inputs
	[t_Scene*] scene: The scene containing the objects.
	[t_ray*] ray: The ray to check for intersections.

	Outputs
	None. The ray's intersection properties are updated based on the closest
	intersection.
*/
void	check_object_intersection(t_Scene *scene, t_ray *ray)
{
	t_Object	*current_object;
	float		distance;
	bool		intersects;

	current_object = scene->objects;
	distance = INFINITY;
	ray->intersects_object = false;
	while (current_object)
	{
		intersects = check_intersection(ray, current_object, &distance);
		if (intersects)
		{
			ray->intersects_object = true;
			if (distance < ray->closest_hit_distance)
			{
				ray->closest_hit_distance = distance;
				ray->closest_object = current_object;
			}
		}
		current_object = current_object->next;
	}
	if (ray->intersects_object)
	{
		// Calculate the normal of the closest object
		calculate_normal(ray);
		// calculate lighting
		calculate_lighting(scene, ray);
		// calculate shadows

		// apply lighting and shadows to ray colour

		// set the ray colour
		// set_ray_colour(ray);
	}
}
