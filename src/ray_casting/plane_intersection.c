#include "../../inc/minirt.h"

bool	ray_intersects_plane(t_Scene *scene, t_Vector3 ray_dir, 				\
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
		return (printf("* "), false);  // ray intersects plane behind camera
}
