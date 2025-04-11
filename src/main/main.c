/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:29:18 by atang             #+#    #+#             */
/*   Updated: 2025/04/11 21:50:43 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

/*
	Summary
	Sets up the MLX window and initializes all necessary event hooks for
	user interaction.

	Inputs
	[t_Scene*] scene: Contains all program data including MLX information
		and window properties.

	Outputs
	None. Function enters MLX event loop which runs until program termination.

	Explanation
	This function finalizes the window setup process by:
	1. Displaying Initial Image:
	   - Puts the rendered image to the window at position (0,0)
	   - Prints confirmation message to console
	   
	2. Setting Up Event Hooks:
	   - Key events for keyboard input handling
	   - Window close button for proper program termination
	   - Window resize for dynamic window size adjustment
	   
	3. Event Loop:
	   - Enters MLX main loop which handles all user interactions
	   - Program remains in this loop until terminated
*/
static void	setup_mlx_window_and_hooks(t_Scene *scene)
{
	mlx_put_image_to_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr, \
		scene->mlx.img_ptr, 0, 0);
	printf(M "\n---> WINDOW OPENED <---\n\n" RST);
	mlx_key_hook(scene->mlx.win_ptr, deal_key, scene);
	mlx_hook(scene->mlx.win_ptr, 17, 0, close_button_hook, scene);
	mlx_hook(scene->mlx.win_ptr, 25, 0, resize_window_hook, scene);
	mlx_loop(scene->mlx.mlx_ptr);
}

/*
	Summary
	Main entry point of the MiniRT ray tracer program. Handles program
	initialization, file validation, and scene setup.

	Inputs
	[int] argc: Number of command line arguments
	[char**] argv: Array of command line argument strings, where argv[1]
		should contain the path to the .rt scene description file

	Outputs
	[int] Returns SUCCESS (0) on successful execution, or 1 on error

	Explanation
	Program execution flow:
	1. Input Validation:
	   - Checks for correct number of arguments
	   - Validates filename format and extension
	   - Verifies file existence and accessibility
	   
	2. Scene Setup:
	   - Initializes scene and memory structures
	   - Parses the RT file to populate scene data
	   - Initializes MLX graphics system
	   
	3. Rendering Pipeline:
	   - Performs ray tracing calculations
	   - Converts ray trace results to image
	   - Sets up window and event handling
	   
	Error Handling:
	- Returns error if incorrect argument count or invalid filename
	- Returns error if file not found or inaccessible
	- Displays appropriate error messages to user
*/
int	main(int argc, char **argv)
{
	t_Scene	scene;
	t_mem	mem;

	if (argc != 2 || filename_error(argv[1]))
	{
		printf(RED "\nError!\n" RST G
			"Correct usage is: ./mini_rt <filename>.rt\n\n" RST);
	}
	else if (file_exists(argv[1]))
	{
		printf(M "\n---> FILE FOUND <---\n" RST);
		if (file_status(argv[1]) != SUCCESS)
			return (1);
		init_scene(&scene, &mem);
		parse_rt_file(argv[1], &scene);
		init_mlx(&scene);
		init_mem(&scene);
		trace_rays(&mem, &scene);
		put_pixels_to_image(&mem, &scene);
		setup_mlx_window_and_hooks(&scene);
	}
	else
		return (err_return("File not found"));
	return (SUCCESS);
}
