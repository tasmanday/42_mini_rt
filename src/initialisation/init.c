/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 21:05:32 by tday              #+#    #+#             */
/*   Updated: 2025/01/31 21:33:11 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

void init_scene(t_Scene *scene)
{
	*scene = (t_Scene){0};
}

/*
	Summary
	Initializes rays for each corner of the pixel grid.

	Inputs
	[t_mem*] mem: The memory structure containing the corner array.
	[t_Scene*] scene: The scene containing the dimensions for the grid.

	Outputs
	None. The corner rays are initialized in the memory structure.
*/
/* void	init_corner_rays(t_mem *mem, t_Scene *scene)
{
	int		y;
	int		x;

	y = 0;
	while (y <= scene->mlx.height)
	{
		x = 0;
		while (x <= scene->mlx.width)
		{
			init_ray(scene, &mem->corners[y][x], x, y);
			x++;
		}
		y++;
	}
} */

/*
	Summary
	Initializes the pixel array with corner references and mid-point rays.

	Inputs
	[t_mem*] mem: The memory structure containing the pixel and corner arrays.
	[t_Scene*] scene: The scene containing the dimensions for the grid.

	Outputs
	None. The pixel array is initialized with corner references and mid-point
	rays.
*/
/* void	init_pixels(t_mem *mem, t_Scene *scene)
{
	int		y;
	int		x;

	y = 0;
	while (y < scene->mlx.height)
	{
		x = 0;
		while (x < scene->mlx.width)
		{
			mem->pixels[y][x].TL = &mem->corners[y][x]; // top left corner
			mem->pixels[y][x].TR = &mem->corners[y][x + 1]; // top right corner
			mem->pixels[y][x].BL = &mem->corners[y + 1][x]; // bottom left corner
			mem->pixels[y][x].BR = &mem->corners[y + 1][x + 1]; // bottom right corner
			mem->pixels[y][x].avg_colour = 0x000000;
			x++;
		}
		y++;
	}
} */

/*
	Summary
	Initializes the pixel and corner arrays for ray tracing.

	Inputs
	[t_mem*] mem: The memory structure to initialize.
	[t_Scene*] scene: The scene containing the dimensions for the arrays.

	Outputs
	None. The memory structure is initialized with pixel and corner arrays.
*/

/*
	Summary
	Initializes the corner rays and the pixel array with corner references and
	mid-point rays.

	Inputs
	[t_mem*] mem: The memory structure containing the pixel and corner arrays.
	[t_Scene*] scene: The scene containing the dimensions for the grid.

	Outputs
	None. The memory structure is initialized with corner rays and pixel array.
*/
void	init_pixel_array(t_mem *mem, t_Scene *scene)
{
	int		y;
	int		x;

	y = 0;
	while (y <= scene->mlx.height)
	{
		x = 0;
		while (x <= scene->mlx.width)
		{
			init_ray(scene, &mem->corners[y][x], x, y);
			if (x < scene->mlx.width && y < scene->mlx.height)
			{
				mem->pixels[y][x].TL = &mem->corners[y][x]; // top left corner
				mem->pixels[y][x].TR = &mem->corners[y][x + 1]; // top right corner
				mem->pixels[y][x].BL = &mem->corners[y + 1][x]; // bottom left corner
				mem->pixels[y][x].BR = &mem->corners[y + 1][x + 1]; // bottom right corner
				mem->pixels[y][x].avg_colour = 0x000000;
			}
			x++;
		}
		y++;
	}
}

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

	pixels = safe_malloc(height * sizeof(t_pixel *), \
		"pixels array malloc error");
	i = 0;
	while (i < height)
	{
		pixels[i] = safe_malloc(width * sizeof(t_pixel), \
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

	corners = safe_malloc((height + 1) * sizeof(t_ray *), \
		"corners array malloc error");
	i = 0;
	while (i <= height)
	{
		corners[i] = safe_malloc((width + 1) * sizeof(t_ray), \
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
