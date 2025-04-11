/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:34:44 by tday              #+#    #+#             */
/*   Updated: 2025/04/11 22:24:52 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef VECTORS_H
# define VECTORS_H

# include "structs.h"

// FUNCTION PROTOTYPES //

t_Vector3	vector(float x, float y, float z);
t_Vector3	vect_normalise(t_Vector3 v);
t_Vector3	vect_add(t_Vector3 a, t_Vector3 b);
t_Vector3	vect_subtract(t_Vector3 a, t_Vector3 b);
t_Vector3	vect_cross(t_Vector3 a, t_Vector3 b);
float		vect_dot(t_Vector3 a, t_Vector3 b);
t_Vector3	vect_multiply_scalar(t_Vector3 v, float scalar);
float		vect_distance(t_Vector3 a, t_Vector3 b);
t_Vector3	vect_reflect(t_Vector3 incident, t_Vector3 normal);

#endif