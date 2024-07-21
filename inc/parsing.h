/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:18:01 by tday              #+#    #+#             */
/*   Updated: 2024/07/21 15:50:44 by tday             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minirt.h"

typedef struct s_elem
{
	char	*id;
	t_coord	*coordinates;
	t_coord	*axis_vector;
	float	ratio;
	float	diameter;
	float	height;
	int		rgb;
}				t_elem;

#endif