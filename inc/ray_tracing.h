/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:35:44 by tday              #+#    #+#             */
/*   Updated: 2025/02/01 19:07:14 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef RAY_TRACING_H
#define RAY_TRACING_H

#include "structs.h"

// STRUCTURES //

typedef struct s_QuadraticCoefficients
{
	float		a;
	float		b;
	float		c;
}				t_Quad;

// FUNCTION PROTOTYPES //

// trace_rays.c //

void		trace_rays(t_mem *mem, t_Scene *scene);


#endif