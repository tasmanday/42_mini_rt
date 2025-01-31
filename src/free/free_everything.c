/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:12:25 by tday              #+#    #+#             */
/*   Updated: 2025/01/31 23:21:29 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

void	free_everything(t_mem *mem, t_Scene *scene)
{
	// Free the mem->pixels array
	if (mem->pixels)
	{
		int i = 0;
		while (i < scene->mlx.height)
		{
			if (mem->pixels[i])
				free(mem->pixels[i]); // Free each row in the mem->pixels array
			i++;
		}
		free(mem->pixels); // Free the top-level pointer
	}

	// Free the mem->corner_ray array
	if (mem->corner_ray)
	{
		int i = 0;
		while (i <= scene->mlx.height)
		{
			if (mem->corner_ray[i])
				free(mem->corner_ray[i]); // Free each row in the mem->corner_ray array
			i++;
		}
		free(mem->corner_ray); // Free the top-level pointer
	}
}
