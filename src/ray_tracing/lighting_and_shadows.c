/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_and_shadows.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 23:16:37 by tday              #+#    #+#             */
/*   Updated: 2025/02/01 17:06:54 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

bool is_in_shadow(t_Scene *scene, t_Vector3 intersection_point, t_Object *ignore_object)
{
	t_ray	shadow_ray;
	float	light_distance;

	// Create shdaow ray from insection point to light source
	shadow_ray.ray_origin = intersection_point;

	// Calculate direction to light
	shadow_ray.ray_dir = vect_subtract(scene->light.position, intersection_point);

	shadow_ray.ray_origin = vect_add(intersection_point, vect_multiply_scalar(shadow_ray.ray_dir, 0.0001f));
	// Calculate distance to light
	light_distance = vect_distance(scene->light.position, intersection_point);
	// Normalise direction
	shadow_ray.ray_dir = vect_normalise(shadow_ray.ray_dir);

	shadow_ray.intersects_object = false;
	shadow_ray.closest_hit_distance = INFINITY;
	shadow_ray.closest_object = NULL;
	shadow_ray.cyl_closest_point = 0;

	// Check for insections between point and light
if (ray_intersects_object(scene, &shadow_ray, ignore_object))
		{
			// If intersection is closer than the light, point is in shadow
			if (shadow_ray.closest_hit_distance < light_distance)
				return (true);
		}
	return (false);
}

void calculate_lighting(t_Light light, t_AmbientLight ambient, t_ray *ray)
{
	t_Vector3	light_dir;
	float		intensity;

	light_dir = vect_normalise(vect_subtract(light.position, vect_multiply_scalar(ray->ray_dir, ray->closest_hit_distance)));
	intensity = vect_dot(light_dir, ray->normal_at_intersection);
	if (intensity < 0)
		intensity = 0.0f;

	ray->colour.r = (ray->colour.r * ambient.ratio * ambient.colour.r) + ray->colour.r * intensity;
	ray->colour.g = (ray->colour.g * ambient.ratio * ambient.colour.g) + ray->colour.g * intensity;
	ray->colour.b = (ray->colour.b * ambient.ratio * ambient.colour.b) + ray->colour.b * intensity;

	// Clamp values
	ray->colour.r = fminf(fmaxf(ray->colour.r, 0.0f), 1.0f);
	ray->colour.g = fminf(fmaxf(ray->colour.g, 0.0f), 1.0f);
	ray->colour.b = fminf(fmaxf(ray->colour.b, 0.0f), 1.0f);
}

void	apply_light_or_shadow(t_Scene *scene, t_ray *ray)
{
	// calculate shadows
	if (is_in_shadow(scene, ray->intersection_point, ray->closest_object))
	{
		ray->colour.r = ray->colour.r * scene->ambient_light.ratio * scene->ambient_light.colour.r;
		ray->colour.g = ray->colour.g * scene->ambient_light.ratio * scene->ambient_light.colour.g;
		ray->colour.b = ray->colour.b * scene->ambient_light.ratio * scene->ambient_light.colour.b;
	}
	else
	{
		// calculate lighting
		calculate_lighting(scene->light, scene->ambient_light, ray);
	} 
}
