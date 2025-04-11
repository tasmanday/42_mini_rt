/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:56:39 by tday              #+#    #+#             */
/*   Updated: 2025/04/11 22:03:14 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

/*
	Summary
	Performs cleanup operations and terminates the program gracefully.

	Inputs
	[t_Scene*] scene: Contains all program data and resources to be freed

	Outputs
	None. Program terminates after cleanup.

	Explanation
	This function handles program termination:
	1. Resource Cleanup:
	   - Destroys MLX window
	   - Frees all allocated memory
	   
	2. User Feedback:
	   - Prints exit message in red color
	   
	3. Program Exit:
	   - Calls exit(1) for immediate termination
	   - Ensures all resources are properly released
*/
void	handle_exit(t_Scene *scene)
{
	mlx_destroy_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr);
	printf(RED "\nExiting...\n\n" RST);
	free_everything(scene);
	exit(1);
}

/*
	Summary
	Transfers the rendered pixel data from memory to the MLX image buffer
	for display.

	Inputs
	[t_mem*] mem: Contains the calculated pixel colors from ray tracing
	[t_Scene*] scene: Contains MLX image data and window dimensions

	Outputs
	None. Updates the MLX image buffer with pixel data.

	Explanation
	This function converts memory pixels to display format:
	1. Pixel Processing:
	   - Iterates through each pixel position (x,y)
	   - Calculates exact memory location in image buffer
	   - Uses bit depth (bpp) to determine pixel spacing
	   
	2. Color Transfer:
	   - Copies averaged color values from memory
	   - Converts to unsigned int format for MLX
	   - Writes directly to image buffer memory
	   
	3. Buffer Management:
	   - Handles proper byte alignment
	   - Ensures correct color representation
	   - Prepares image for display in window
*/
void	put_pixels_to_image(t_mem *mem, t_Scene *scene)
{
	int		x;
	int		y;
	char	*pixel;

	y = 0;
	while (y < scene->mlx.height)
	{
		x = 0;
		while (x < scene->mlx.width)
		{
			pixel = scene->mlx.img_data + (y * scene->mlx.size_line + \
				x * (scene->mlx.bpp / 8));
			*(unsigned int *)pixel = mem->pixels[y][x].avg_colour;
			x++;
		}
		y++;
	}
}
