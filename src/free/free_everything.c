/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:12:25 by tday              #+#    #+#             */
/*   Updated: 2025/02/02 13:41:17 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

/*
	Summary
	Frees all dynamically allocated memory in the program.

	Inputs
	[t_mem*] mem: Pointer to the memory structure containing allocated arrays.
	[t_Scene*] scene: Pointer to the scene structure containing window dimensions.

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
void	free_everything(t_mem *mem, t_Scene *scene)
{
	if (mem->pixels)
	{
		int i = 0;
		while (i < scene->mlx.height)
		{
			if (mem->pixels[i])
				free(mem->pixels[i]);
			i++;
		}
		free(mem->pixels);
	}
	if (mem->corner_ray)
	{
		int i = 0;
		while (i <= scene->mlx.height)
		{
			if (mem->corner_ray[i])
				free(mem->corner_ray[i]);
			i++;
		}
		free(mem->corner_ray);
	}
	printf(M "all alocated memory freed\n" RST);
}
