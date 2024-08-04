/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:18:01 by tday              #+#    #+#             */
/*   Updated: 2024/08/04 23:46:35 by tday             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "types.h"

typedef struct s_amb
{
	char		*id;
	float		ratio;
	t_rgb		*rgb;
}				t_amb;

typedef struct s_light
{
	char		*id;
	t_coord		*coordinates;
	float		ratio;
	t_rgb		*rgb;
}				t_light;

typedef struct s_cam
{
	char		*id;
	t_coord		*coordinates;
	t_vect		*orientation;
	int			fov;
}				t_cam;

typedef struct s_objs
{
	char		*id;
	t_coord		*coordinates;
	t_coord		*axis_vector;
	float		diameter;
	float		height;
	t_rgb		*rgb;
}				t_objs;

#endif
