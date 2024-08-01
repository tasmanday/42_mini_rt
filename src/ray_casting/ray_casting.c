/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:57:06 by tday              #+#    #+#             */
/*   Updated: 2024/08/01 23:46:54 by tday             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

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
	normalised_vector = {v.x / len, v.y / len, v.z / len};
	return (normalised_vector);
}

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
	ray_dir = {px, py, -1};
	ray_dir = normalize(ray_dir);
	return (ray_dir);
}
