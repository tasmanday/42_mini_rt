/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 21:05:32 by tday              #+#    #+#             */
/*   Updated: 2025/04/12 09:07:49 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/*
	Summary
	Initializes a scene structure by setting all its members to zero.

	Inputs
	[t_Scene*] scene: Pointer to the scene structure to initialize.

	Outputs
	None. Modifies the scene structure in place.

	Explanation
	Uses compound literal syntax to zero-initialize all members of the scene
	structure, ensuring a clean initial state before scene setup begins.
*/
void	init_scene(t_Scene *scene, t_mem *mem)
{
	*scene = (t_Scene){0};
	scene->mem = mem;
}

/*
	Summary
	Initializes the corner rays and pixel array for the entire image, setting
	up the structure needed for anti-aliased ray tracing.

	Inputs
	[t_mem*] mem: Contains the pixel and corner ray arrays to initialize.
	[t_Scene*] scene: Contains the image dimensions.

	Outputs
	None. Initializes both the corner ray array and links corners to pixels.

	Explanation
	1. Corner Ray Setup:
	   - Creates a grid of rays (width+1 × height+1)
	   - Each ray represents a corner point where pixels meet
	   - Initializes each ray with proper direction based on position

	2. Pixel Corner Assignment:
	   - For each pixel (width × height):
	   - Links to its four corner rays:
	     * tl: Current position (y,x)
	     * tr: Right neighbor (y,x+1)
	     * bl: Bottom neighbor (y+1,x)
	     * br: Bottom-right neighbor (y+1,x+1)
	   - Sets initial average color to black

	Note: The corner ray grid is one unit larger in each dimension than the
	pixel grid, as each pixel needs four corners for anti-aliasing.
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
				mem->pixels[y][x].tl = &mem->corner_ray[y][x];
				mem->pixels[y][x].tr = &mem->corner_ray[y][x + 1];
				mem->pixels[y][x].bl = &mem->corner_ray[y + 1][x];
				mem->pixels[y][x].br = &mem->corner_ray[y + 1][x + 1];
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

	Explanation
	1. Allocate Row Pointers:
	   - Creates array of height pointers using safe_malloc
	   - Each pointer will point to a row of pixels

	2. Allocate Each Row:
	   - For each row, allocates width * sizeof(t_pixel) bytes
	   - Uses safe_malloc to handle allocation failures

	Note: Uses safe_malloc which handles error checking and reporting,
	ensuring robust memory allocation.
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
	[int] width: The width of the pixel array.
	[int] height: The height of the pixel array.

	Outputs
	[t_ray**] Returns a pointer to the allocated 2D array of rays.

	Explanation
	1. Allocate Row Pointers:
	   - Creates array of (height + 1) pointers using safe_malloc
	   - Extra row needed because corners form a grid one larger than pixels

	2. Allocate Each Row:
	   - For each row, allocates (width + 1) * sizeof(t_ray) bytes
	   - Extra column needed for same reason as extra row
	   - Uses safe_malloc to handle allocation failures

	Note: Array dimensions are (width+1) × (height+1) because corner rays
	exist at the edges of pixels, requiring an extra row and column.
*/
t_ray	**allocate_corner_arry(int width, int height)
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

	Explanation
	Allocates two main data structures needed for ray tracing:
	1. Pixel array: Stores final color values and corner references
	2. Corner ray array: Stores the rays used for anti-aliasing
*/
void	init_mem(t_Scene *scene)
{
	scene->mem->pixels = allocate_pixel_array(scene->mlx.width, \
		scene->mlx.height);
	scene->mem->corner_ray = allocate_corner_arry(scene->mlx.width, \
		scene->mlx.height);
}
