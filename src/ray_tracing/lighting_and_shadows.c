/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_and_shadows.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 23:16:37 by tday              #+#    #+#             */
/*   Updated: 2025/04/10 01:05:54 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

/*
	Summary
	Determines if a point on an object is in shadow by checking if any other
	objects block the light path.

	Inputs
	[t_Scene*] scene: The scene containing objects and light source.
	[t_Vector3] intersection_point: The point to check for shadows.
	[t_Object*] ignore_object: The object the point is on (to prevent
		self-shadowing).

	Outputs
	[bool] Returns true if the point is in shadow, false if it's lit.

	Explanation
	1. Initialize Shadow Ray:
	   - Set origin to intersection point
	   - Calculate direction to light source
	   - Offset origin slightly along direction (epsilon 0.0001) to prevent
	     self-intersection artifacts

	2. Setup Ray Parameters:
	   - Calculate total distance to light
	   - Normalize the direction vector
	   - Initialize intersection tracking variables

	3. Check for Occlusion:
	   - Test for intersections with all objects (except ignore_object)
	   - Compare closest hit distance with distance to light
	   - Return true if any object blocks the path to light
*/
bool	is_in_shadow(t_Scene *scene, t_Vector3 intersection_point, \
			t_Object *ignore_object)
{
	t_ray	shadow_ray;
	float	light_distance;

	shadow_ray.ray_origin = intersection_point;
	shadow_ray.ray_dir = vect_subtract(scene->light.position, \
		intersection_point);
	shadow_ray.ray_origin = vect_add(intersection_point, \
		vect_multiply_scalar(shadow_ray.ray_dir, 0.0001f));
	light_distance = vect_distance(scene->light.position, intersection_point);
	shadow_ray.ray_dir = vect_normalise(shadow_ray.ray_dir);
	shadow_ray.intersects_object = false;
	shadow_ray.closest_hit_distance = INFINITY;
	shadow_ray.closest_object = NULL;
	shadow_ray.cyl_closest_point = 0;
	if (ray_intersects_object(scene, &shadow_ray, ignore_object))
	{
		if (shadow_ray.closest_hit_distance < light_distance)
			return (true);
	}
	return (false);
}

/*
	Summary
	Calculates the final color of a point by combining ambient light and
	diffuse lighting based on the angle between the surface normal and the
	light direction.

	Inputs
	[t_Light] light: The scene's light source information.
	[t_AmbientLight] ambient: The scene's ambient light settings.
	[t_ray*] ray: Contains intersection information and color to be modified.

	Outputs
	None. Updates ray->colour with the final lit and clamped color values.

	Explanation
	This function implements basic Lambertian diffuse reflection:
	1. Calculate Light Direction:
	   - Finds normalized vector from intersection point to light source
	   
	2. Compute Light Intensity:
	   - Uses dot product between light direction and surface normal
	   - Clamps negative values to zero (back-face lighting)
	   
	3. Apply Ambient Light:
	   - Multiplies base color by ambient light color and ratio
	   
	4. Apply Diffuse Light:
	   - Adds directional light contribution scaled by intensity
	   
	5. Clamp Results:
	   - Ensures all color components stay within [0,1] range

	The result provides basic 3D shading with both ambient and directional
	lighting components.
*/
void	calculate_lighting(t_Light light, t_AmbientLight ambient, t_ray *ray)
{
	t_Vector3	light_dir;
	float		intensity;

	light_dir = vect_normalise(vect_subtract(light.position, \
		vect_multiply_scalar(ray->ray_dir, ray->closest_hit_distance)));
	intensity = vect_dot(light_dir, ray->normal_at_intersection);
	if (intensity < 0)
		intensity = 0.0f;
	ray->colour.r = (ray->colour.r * ambient.ratio * ambient.colour.r) + \
		ray->colour.r * intensity;
	ray->colour.g = (ray->colour.g * ambient.ratio * ambient.colour.g) + \
		ray->colour.g * intensity;
	ray->colour.b = (ray->colour.b * ambient.ratio * ambient.colour.b) + \
		ray->colour.b * intensity;
	ray->colour.r = fminf(fmaxf(ray->colour.r, 0.0f), 1.0f);
	ray->colour.g = fminf(fmaxf(ray->colour.g, 0.0f), 1.0f);
	ray->colour.b = fminf(fmaxf(ray->colour.b, 0.0f), 1.0f);
}

/*
	Summary
	Determines whether a point is in shadow and applies appropriate lighting
	calculations.

	Inputs
	[t_Scene*] scene: Contains light sources and scene objects.
	[t_ray*] ray: Contains intersection information and color to be modified.

	Outputs
	None. Updates ray->colour with either shadowed or lit color values.

	Explanation
	This function handles the final lighting step:
	1. Check for Shadows:
	   If the point is in shadow:
	   - Apply only ambient lighting (darkened version of base color)
	   
	2. If Not in Shadow:
	   - Apply full lighting calculation including both ambient and diffuse
	     components

	This creates the contrast between lit and shadowed areas in the scene.
*/
void	apply_light_or_shadow(t_Scene *scene, t_ray *ray)
{
	if (is_in_shadow(scene, ray->intersection_point, ray->closest_object))
	{
		ray->colour.r = ray->colour.r * scene->ambient_light.ratio * \
			scene->ambient_light.colour.r;
		ray->colour.g = ray->colour.g * scene->ambient_light.ratio * \
			scene->ambient_light.colour.g;
		ray->colour.b = ray->colour.b * scene->ambient_light.ratio * \
			scene->ambient_light.colour.b;
	}
	else
	{
		calculate_lighting(scene->light, scene->ambient_light, ray);
	}
}
