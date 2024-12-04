/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:12:25 by tday              #+#    #+#             */
/*   Updated: 2024/12/05 08:26:02 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

void free_everything(t_mem *mem, t_Scene scene)
{
	// Free the mem->pixels array
	if (mem->pixels)
	{
		int i = 0;
		while (i < scene.mlx.height)
		{
			if (mem->pixels[i])
				free(mem->pixels[i]); // Free each row in the mem->pixels array
			i++;
		}
		free(mem->pixels); // Free the top-level pointer
	}

	// Free the mem->corners array
	if (mem->corners)
	{
		int i = 0;
		while (i <= scene.mlx.height)
		{
			if (mem->corners[i])
				free(mem->corners[i]); // Free each row in the mem->corners array
			i++;
		}
		free(mem->corners); // Free the top-level pointer
	}
}
