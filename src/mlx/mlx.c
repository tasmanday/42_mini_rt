/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:58:17 by atang             #+#    #+#             */
/*   Updated: 2025/02/01 23:13:12 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

// NEW! Added to handle window resizing
int	expose_hook(t_Scene *scene)
{
	mlx_put_image_to_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr,
			scene->mlx.img_ptr, 0, 0);
	return (SUCCESS);
}

// NEW! Added to handle window resizing
int	resize_window_hook(int width, int height, t_Scene *scene, t_mem *mem)
{
	scene->mlx.width = (int)width;
	scene->mlx.height = (int)height;

	if (width <= 0 || height  <= 0)
		return (0);
	if (scene->mlx.img_ptr) // Destroy image if it already exists; prevents leaks
		mlx_destroy_image(scene->mlx.mlx_ptr, scene->mlx.img_ptr);
	scene->mlx.img_ptr = mlx_new_image(scene->mlx.mlx_ptr, width, height);
	scene->mlx.img_data = mlx_get_data_addr(scene->mlx.img_ptr,
			&scene->mlx.bpp, &scene->mlx.size_line, &scene->mlx.endian);
	trace_rays(mem, scene);
	put_pixels_to_image(mem, scene);
	mlx_put_image_to_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr,
			scene->mlx.img_ptr, 0, 0);
	return (SUCCESS);
}

void	initialise_data(t_Scene	*scene)
{
	scene->mlx.amplify = 1;
	scene->mlx.mlx_ptr = mlx_init();
	scene->mlx.win_ptr = mlx_new_window(scene->mlx.mlx_ptr, scene->mlx.width,
			scene->mlx.height, "miniRT");
	scene->mlx.img_ptr = mlx_new_image(scene->mlx.mlx_ptr, scene->mlx.width,
			scene->mlx.height);
	scene->mlx.img_data = mlx_get_data_addr(scene->mlx.img_ptr,
			&scene->mlx.bpp, &scene->mlx.size_line, &scene->mlx.endian);
	mlx_hook(scene->mlx.win_ptr, 17, 0, close_button_hook, scene);
	mlx_hook(scene->mlx.win_ptr, 25, 0, resize_window_hook, scene); // NEW! Added to adapt to resize dimension changes
	mlx_expose_hook(scene->mlx.win_ptr, expose_hook, scene); // NEW! Added to handle redraw after resize
	scene->mlx.zoom = 20;
}

int	deal_key(int key, t_Scene *scene)
{
	printf("%d\n", key);
	if (key == 126 || key == 65362)
		scene->mlx.shift_y -= 50;
	else if (key == 125 || key == 65364)
		scene->mlx.shift_y += 50;
	else if (key == 123 || key == 65361)
		scene->mlx.shift_x -= 50;
	else if (key == 124 || key == 65363)
		scene->mlx.shift_x += 50;
	else if (key == 53 || key == 65307)
		handle_exit(scene);
	return (SUCCESS);
}

int	close_button_hook(t_Scene *scene)
{
	handle_exit(scene);
	return (0);
}

void	handle_exit(t_Scene *scene)
{
	mlx_destroy_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr);
	printf(RED "\nExiting...\n\n" RST);
//	free_everything(&mem, &scene); // TODO make this work &mem not being passed to this function
	exit(1);
}

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
			pixel = scene->mlx.img_data + (y * scene->mlx.size_line + x * (scene->mlx.bpp / 8));
			*(unsigned int *)pixel = mem->pixels[y][x].avg_colour;
			x++;
		}
		y++;
	}
}
