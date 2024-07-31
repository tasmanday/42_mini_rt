/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:57:06 by tday              #+#    #+#             */
/*   Updated: 2024/07/31 16:57:06 by tday             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_vect	normalise_vector(t_vect v)
{
	double	len;
	t_vect	normalised_vector;

	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	normalised_vector = {v.x / len, v.y / len, v.z / len};
	return (normalised_vector);
}