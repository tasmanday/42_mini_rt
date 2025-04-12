/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:58:17 by atang             #+#    #+#             */
/*   Updated: 2025/04/12 09:07:16 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/*
	Summary
	Handles window exposure events by redrawing the current image to the window.

	Inputs
	[t_Scene*] scene: Contains all program data including MLX information
		and the current image to be displayed.

	Outputs
	[int] Returns SUCCESS (0) after redrawing the image.

	Explanation
	This function is called when the window needs to be redrawn:
	1. Window Redraw:
	   - Retrieves the current image from scene data
	   - Redraws the image at position (0,0) in the window
	   - Ensures window content is properly displayed after exposure events
		 (e.g., when window is uncovered or brought to foreground)
*/
int	expose_hook(t_Scene *scene)
{
	mlx_put_image_to_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr, \
		scene->mlx.img_ptr, 0, 0);
	return (SUCCESS);
}

/*
	Summary
	Handles window resize events by recreating and redrawing the scene at
	the new dimensions.

	Inputs
	[int] width: New window width in pixels
	[int] height: New window height in pixels
	[t_Scene*] scene: Contains all program data and MLX information
	[t_mem*] mem: Contains memory structures for ray tracing

	Outputs
	[int] Returns SUCCESS (0) on successful resize, or 0 if invalid dimensions

	Explanation
	This function performs a complete window resize operation:
	1. Dimension Validation:
	   - Updates stored window dimensions
	   - Validates new dimensions are positive
	   
	2. Image Management:
	   - Destroys existing image to prevent memory leaks
	   - Creates new image buffer with updated dimensions
	   - Updates image data address and properties
	   
	3. Scene Rerendering:
	   - Performs new ray tracing calculations for updated dimensions
	   - Converts traced rays to pixel data
	   - Displays new image in resized window
	   
	Error Handling:
	- Returns early if width or height are non-positive
	- Ensures clean destruction of existing image before recreation
*/
int	resize_window_hook(int width, int height, t_Scene *scene, t_mem *mem)
{
	scene->mlx.width = (int)width;
	scene->mlx.height = (int)height;
	if (width <= 0 || height <= 0)
		return (0);
	if (scene->mlx.img_ptr)
		mlx_destroy_image(scene->mlx.mlx_ptr, scene->mlx.img_ptr);
	scene->mlx.img_ptr = mlx_new_image(scene->mlx.mlx_ptr, width, height);
	scene->mlx.img_data = mlx_get_data_addr(scene->mlx.img_ptr,
			&scene->mlx.bpp, &scene->mlx.size_line, &scene->mlx.endian);
	trace_rays(mem, scene);
	put_pixels_to_image(mem, scene);
	mlx_put_image_to_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr, \
		scene->mlx.img_ptr, 0, 0);
	return (SUCCESS);
}

/*
	Summary
	Initializes the MLX graphics system and sets up the window with default
	parameters and event hooks.

	Inputs
	[t_Scene*] scene: Contains all program data including MLX information
		to be initialized.

	Outputs
	None. Initializes MLX-related fields in the scene structure.

	Explanation
	This function sets up the basic graphics environment:
	1. Default Configuration:
	   - Sets window dimensions (1920x1080)
	   - Initializes amplification and zoom factors
	   
	2. MLX Setup:
	   - Initializes MLX connection
	   - Creates main window with title "miniRT"
	   - Creates image buffer for rendering
	   - Gets image data address and properties
	   
	3. Event Hook Setup:
	   - Window close button handler
	   - Window resize event handler
	   - Window exposure (redraw) handler
*/
void	init_mlx(t_Scene	*scene)
{
	scene->mlx.height = 1080;
	scene->mlx.width = 1920;
	scene->mlx.amplify = 1;
	scene->mlx.mlx_ptr = mlx_init();
	scene->mlx.win_ptr = mlx_new_window(scene->mlx.mlx_ptr, scene->mlx.width,
			scene->mlx.height, "miniRT");
	scene->mlx.img_ptr = mlx_new_image(scene->mlx.mlx_ptr, scene->mlx.width,
			scene->mlx.height);
	scene->mlx.img_data = mlx_get_data_addr(scene->mlx.img_ptr,
			&scene->mlx.bpp, &scene->mlx.size_line, &scene->mlx.endian);
	mlx_hook(scene->mlx.win_ptr, 17, 0, close_button_hook, scene);
	mlx_hook(scene->mlx.win_ptr, 25, 0, resize_window_hook, scene);
	mlx_expose_hook(scene->mlx.win_ptr, expose_hook, scene);
	scene->mlx.zoom = 20;
}

/*
	Summary
	Processes keyboard input events and performs corresponding view
	transformations or program control actions.

	Inputs
	[int] key: Keycode of the pressed key
	[t_Scene*] scene: Contains all program data including view parameters

	Outputs
	[int] Returns SUCCESS (0) after processing the key event

	Explanation
	This function handles keyboard navigation and control:
	1. View Navigation:
	   - Up arrow (126/65362): Shift view up
	   - Down arrow (125/65364): Shift view down
	   - Left arrow (123/65361): Shift view left
	   - Right arrow (124/65363): Shift view right
	   
	2. Program Control:
	   - ESC key (53/65307): Exit program
	   
	3. Debug Feature:
	   - Prints pressed key code to console
*/
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

/*
	Summary
	Handles window close button (X) events by initiating program shutdown.

	Inputs
	[t_Scene*] scene: Contains all program data needed for cleanup

	Outputs
	[int] Returns 0 after initiating program exit

	Explanation
	This function provides clean program termination:
	1. Exit Handling:
	   - Calls handle_exit to perform cleanup operations
	   - Ensures proper resource deallocation
	   - Provides clean exit point for window close events
*/
int	close_button_hook(t_Scene *scene)
{
	handle_exit(scene);
	return (0);
}
