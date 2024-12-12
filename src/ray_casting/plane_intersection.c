
#include "../../inc/minirt.h"

bool	ray_intersects_plane(t_ray *ray, t_Vector3	point_on_plane, \
		t_Vector3	plane_norm_vect, float *distance)
{
	float		denominator;

	plane_norm_vect = vect_normalise(plane_norm_vect);

	denominator = vect_dot(plane_norm_vect, ray->ray_dir);
	if (fabs(denominator) < 1e-6)
		return (false); // miss, ray parallel to plane, plane_norm_vect perpendicular to ray_dir
	*distance = vect_dot(plane_norm_vect, \
		vect_subtract(point_on_plane, ray->ray_origin)) / denominator;
	if (*distance <= 0) //because the camera looks towards the negative z by default
	{
		*distance *= -1; // fixes the negative distance
		return (true); // ray intersects plane in front of camera
	}
	else
	{
		*distance = INFINITY;
		return (false);  // ray intersects plane behind camera
	}
}

/* bool	ray_intersects_plane(t_Scene *scene, t_Vector3 ray_dir, 				\
		float *distance)
{
	t_Vector3	ray_origin;
	t_Vector3	point_on_plane;
	t_Vector3	plane_norm_vect;
	float		denominator;

	ray_origin = scene->camera.position;
	point_on_plane = scene->objects->u_data.plane.point;
	plane_norm_vect = scene->objects->u_data.plane.normal;
	denominator = vect_dot(plane_norm_vect, ray_dir);
	if (denominator == 0)
		return (printf("_ "), false); // miss, ray parallel to plane
	*distance = (vect_dot(plane_norm_vect, \
		vect_subtract(point_on_plane, ray_origin))) / denominator;
	if (*distance > 0)
		return (printf("O "), true); // ray intersects plane in front of camera
	else
		return (printf("* "), false);  // ray intersects plane behind camera // TODO clear distance
} */