/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:06:45 by tday              #+#    #+#             */
/*   Updated: 2025/01/01 15:31:26 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

/*
	Summary
	Allocates memory for a 2D array of pixels with the specified width and
	height.

	Inputs
	[int] width: The width of the pixel array.
	[int] height: The height of the pixel array.

	Outputs
	[t_pixel**] Returns a pointer to the allocated 2D array of pixels.
*/
t_pixel	**allocate_pixel_array(int width, int height)
{
	t_pixel	**pixels;
	int		i;

	pixels = safe_calloc(height * sizeof(t_pixel *), \
		"pixels array malloc error");
	i = 0;
	while (i < height)
	{
		pixels[i] = safe_calloc(width * sizeof(t_pixel), \
			"pixels array malloc error");
		i++;
	}
	return (pixels);
}

/*
	Summary
	Allocates memory for a 2D array of rays representing the corners of a grid.

	Inputs
	[int] width: The width of the corner array.
	[int] height: The height of the corner array.

	Outputs
	[t_ray**] Returns a pointer to the allocated 2D array of rays.
*/
t_ray	**allocate_corner_array(int width, int height)
{
	t_ray	**corners;
	int		i;

	corners = safe_calloc((height + 1) * sizeof(t_ray *), \
		"corners array malloc error");
	i = 0;
	while (i <= height)
	{
		corners[i] = safe_calloc((width + 1) * sizeof(t_ray), \
			"corners array malloc error");
		i++;
	}
	return (corners);
}

/*
	Summary
	Initializes memory for the pixel and corner arrays in the given memory
	structure.

	Inputs
	[t_mem*] mem: The memory structure to initialize.
	[t_Scene*] scene: The scene containing the dimensions for the arrays.

	Outputs
	None. The memory structure is initialized with allocated arrays.
*/
void	init_mem(t_mem *mem, t_Scene *scene)
{
	mem->pixels = allocate_pixel_array(scene->mlx.width, scene->mlx.height);
	mem->corners = allocate_corner_array(scene->mlx.width, scene->mlx.height);
}
