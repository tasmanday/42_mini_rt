/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:41:32 by tday              #+#    #+#             */
/*   Updated: 2025/04/09 23:48:34 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

/*
	Summary
	Frees all dynamically allocated memory in the program.

	Inputs
	[t_mem*] mem: Pointer to the memory structure containing allocated arrays.
	[t_Scene*] scene: Pointer to the scene structure containing window
	dimensions.

	Outputs
	None. Frees the memory and prints a confirmation message.
	
	Explanation
	This function performs a complete cleanup of the program's dynamic memory:
	1. Frees the pixels array, which is a 2D array storing color information for
		each pixel:
	   - First frees each row of pixel data
	   - Then frees the array of row pointers
	2. Frees the corner_ray array, which stores ray information for the corners
		of each pixel:
	   - First frees each row of ray data
	   - Then frees the array of row pointers
	The function checks for NULL pointers before attempting to free memory to
	prevent segmentation faults. After cleanup, it confirms successful memory
	deallocation with a message.
*/
void	free_everything(t_Scene *scene)
{
	int	i;

	if (scene->mem->pixels)
	{
		i = 0;
		while (i < scene->mlx.height)
		{
			if (scene->mem->pixels[i])
				free(scene->mem->pixels[i]);
			i++;
		}
		free(scene->mem->pixels);
	}
	if (scene->mem->corner_ray)
	{
		i = 0;
		while (i <= scene->mlx.height)
		{
			if (scene->mem->corner_ray[i])
				free(scene->mem->corner_ray[i]);
			i++;
		}
		free(scene->mem->corner_ray);
	}
	printf(M "all alocated memory freed\n" RST);
}
