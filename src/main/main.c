/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:29:18 by atang             #+#    #+#             */
/*   Updated: 2025/02/01 00:15:07 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

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
		init_scene(&scene);
		printf("init_scene called\n"); // TODO remove
		parse_rt_file(argv[1], &scene);
		printf("parse_rt_file called\n"); // TODO remove
		scene.mlx.height = 1080; // TODO put in init_mlx needs to be at start
		scene.mlx.width = 1920; // TODO put in init_mlx needs to be at start
		initialise_data(&scene); // TODO change name to init_mlx
		printf("initialise_data called\n"); // TODO remove
		init_mem(&mem, &scene);
		printf("init_mem called\n"); // TODO remove
		trace_rays(&mem, &scene);
		printf("trace_rays called\n"); // TODO remove
		put_pixels_to_image(&mem, &scene);
		printf("put_pixels_to_image called\n"); // TODO remove
		mlx_put_image_to_window(scene.mlx.mlx_ptr, scene.mlx.win_ptr, scene.mlx.img_ptr, 0, 0);
		printf("mlx_put_image_to_window called\n"); // TODO remove 

		printf(M "\n---> WINDOW OPENED <---\n\n" RST);
		mlx_key_hook(scene.mlx.win_ptr, deal_key, &scene);
		mlx_hook(scene.mlx.win_ptr, 17, 0, close_button_hook, &scene);
		mlx_hook(scene.mlx.win_ptr, 25, 0, resize_window_hook, &scene);
		mlx_loop(scene.mlx.mlx_ptr);

		free_everything(&mem, &scene);
	}
	else
		return (err_return("File not found"));
	return (SUCCESS);
}
