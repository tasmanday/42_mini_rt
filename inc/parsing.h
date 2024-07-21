/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:18:01 by tday              #+#    #+#             */
/*   Updated: 2024/07/21 14:52:52 by tday             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minirt.h"

typedef struct s_a
{
	char	*id;
	float	ratio;
	int		rgb;
}				t_a;

typedef struct s_l
{
	char	*id;
	t_coord	*coordinates;
	float	ratio;
	int		rgb;
}				t_l;

typedef struct s_c
{
	char	*id;
	t_coord	*coordinates;
	t_coord	*vector;
	float	ratio;
}				t_c;

typedef struct s_sp
{
	char	*id;
	t_coord	*coordinates;
	float	diameter;
	int		rgb;
}				t_sp;

typedef struct s_pl
{
	char	*id;
	t_coord	*coordinates;
	t_coord	*vector;
	int		rgb;
}				t_pl;

typedef struct s_cy
{
	char	*id;
	t_coord	*coordinates;
	t_coord	*axis_vector;
	float	diameter;
	float	height;
	int		rgb;
}				t_cy;

#endif