/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 21:05:32 by tday              #+#    #+#             */
/*   Updated: 2025/02/01 00:15:07 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

void init_scene(t_Scene *scene)
{
	*scene = (t_Scene){0};
}

/*
	Summary
	Initializes the corner rays and the pixel array with corner references for
	ray tracing.

	Inputs
	[t_mem*] mem: The memory structure containing the pixel and corner arrays.
	[t_Scene*] scene: The scene containing the dimensions for the grid.

	Outputs
	None. The memory structure is initialized with corner rays. Each pixel is
	linked to its corresponding corner rays and initialized with an average
	color of black (0x000000).
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
			init_ray(scene, &mem->corner_ray[y][x], x, y);
			if (x < scene->mlx.width && y < scene->mlx.height)
			{
				mem->pixels[y][x].TL = &mem->corner_ray[y][x]; // top left corner
				mem->pixels[y][x].TR = &mem->corner_ray[y][x + 1]; // top right corner
				mem->pixels[y][x].BL = &mem->corner_ray[y + 1][x]; // bottom left corner
				mem->pixels[y][x].BR = &mem->corner_ray[y + 1][x + 1]; // bottom right corner
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
	mem->corner_ray = allocate_corner_array(scene->mlx.width, scene->mlx.height);
}

/*
	Summary
	Initializes a ray with its origin, direction, and default intersection
	properties.

	Inputs
	[t_Scene*] scene: The scene containing the camera position.
	[t_ray*] ray: The ray to initialize.
	[int] x: The x-coordinate of the pixel.
	[int] y: The y-coordinate of the pixel.

	Outputs
	None. The ray is initialized with its origin, direction, and default
	properties.
*/
void	init_ray(t_Scene *scene, t_ray *ray, int x, int y)
{
	ray->ray_origin = scene->camera.position;
	ray->ray_dir = get_ray_direction(scene, x, y);
	ray->intersects_object = false;
	ray->closest_hit_distance = INFINITY;
	ray->closest_object = NULL;
	ray->colour.r = 0;
	ray->colour.g = 0;
	ray->colour.b = 0;
}
