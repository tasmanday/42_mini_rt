/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:15:42 by tday              #+#    #+#             */
/*   Updated: 2025/04/11 22:21:22 by tday             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITIALISATION_H
# define INITIALISATION_H

# include "structs.h"

// FUNCTION PROTOTYPES //

void		init_scene(t_Scene *scene, t_mem *mem);
void		init_pixel_array(t_mem *mem, t_Scene *scene);
t_pixel		**allocate_pixel_array(int width, int height);
t_ray		**allocate_corner_arry(int width, int height);
void		init_mem(t_Scene *scene);
void		init_ray(t_Scene *scene, t_ray *ray, int x, int y);

#endif
