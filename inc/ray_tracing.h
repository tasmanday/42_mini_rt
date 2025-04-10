/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:35:44 by tday              #+#    #+#             */
/*   Updated: 2025/02/01 23:00:20 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef RAY_TRACING_H
#define RAY_TRACING_H

# include <stdbool.h>
# include "structs.h"

// STRUCTURES //

typedef struct s_QuadraticCoefficients
{
	float		a;
	float		b;
	float		c;
}				t_Quad;

// FUNCTION PROTOTYPES //

// compute_ray_directions.c //

t_Vector3	get_ray_direction(t_Scene *scene, int x, int y);
t_Vector3	apply_camera_orientation(t_Vector3 ray, t_Scene *scene);
bool		camera_pointed_straight_up_or_down(t_Vector3 orientation);

// trace_rays.c //

void		trace_rays(t_mem *mem, t_Scene *scene);
void		render_scene(t_mem *mem, t_Scene *scene);
void		set_ray_colour(t_ray *ray);

// intersection.c //

bool		ray_intersects_object(t_Scene *scene, t_ray *ray, \
			t_Object *ignore_obj);
bool		check_intersection(t_ray *ray, t_Object *object, float *distance);
void		update_closest_object(t_ray *ray, t_Object *object, float distance);
void		calculate_intersection(t_ray *ray);
void		calculate_intersection_point(t_ray *ray);

// plane_intersection.c //

bool		ray_intersects_plane(t_ray *ray, t_Vector3	point_on_plane, \
			t_Vector3	plane_norm_vect, float *distance);

// sphere_intersection.c //

bool		ray_intersects_sphere(t_ray *ray, t_Sphere sphere, float *distance);
bool		find_closest_intersection(float tc, float radius2, float d2, \
			float *distance);
bool		ray_misses_sphere(float l2, float tc, float radius2);
bool		ray_pointing_away(t_Vector3 l, t_Vector3 ray_dir);

// cylinder_intersection.c //

bool		ray_intersects_cylinder(t_ray *ray, t_Cylinder cyl, float *distance);
void		check_end_cap(t_ray *ray, t_Cylinder cyl, float distance[4]);
bool		within_radius(t_Vector3 contact_point, t_Vector3 cap_center, \
			float radius);
void		check_cylinder_body(t_ray *ray, t_Cylinder cyl, float distance[4]);
void		calculate_contact_distances(t_ray *ray, t_Cylinder cyl, \
			float t[2]);
bool		contact_point_within_cylinder_height(t_ray *ray, t_Cylinder cyl, \
			float t);

// normal_at_intersection.c //

void		calculate_normal_at_intersection(t_ray *ray);
void		calculate_normal_at_sphere(t_ray *ray);
void		calculate_normal_at_cylinder(t_ray *ray);
void		calculate_normal_cylinder_cap(t_ray *ray, t_Cylinder cyl);
void		calculate_normal_cylinder_body(t_ray *ray, t_Cylinder cyl);

// lighting_and_shadows.c //

void		apply_light_or_shadow(t_Scene *scene, t_ray *ray);
void		calculate_lighting(t_Light light, t_AmbientLight ambient, \
			t_ray *ray);
bool		is_in_shadow(t_Scene *scene, t_Vector3 intersection_point, \
			t_Object *ignore_object);

// anti-aliasing.c //

void	average_pixel_colours(t_mem *mem, t_Scene *scene);
void	calculate_average_colour(t_pixel *pixel);
unsigned int	fill_rgb(float r, float g, float b, unsigned int alpha);

#endif
