/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:29:18 by atang             #+#    #+#             */
/*   Updated: 2025/01/06 17:27:09 by tday             ###   ########.fr       */
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
		scene.ambient_light_parsed = 0;
		scene.camera_parsed = 0;
		scene.light_parsed = 0;
		scene.object_count = 0;
		parse_rt_file(argv[1], &scene);

		scene.mlx.height = 1080;
		scene.mlx.width = 1920;

		initialise_data(&scene);
		printf("initialise_data called\n"); // TODO remove
//		printf("camera orientation: %f, %f, %f\n", scene.camera.orientation.x, scene.camera.orientation.y, scene.camera.orientation.z);
//		printf("plane coordinates: %f, %f, %f\n", scene.objects->u_data.plane.point.x, scene.objects->u_data.plane.point.y, scene.objects->u_data.plane.point.z);
//		printf("plane normal: %f, %f, %f\n", scene.objects->u_data.plane.normal.x, scene.objects->u_data.plane.normal.y, scene.objects->u_data.plane.normal.z);
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

/*		// testing intersection
		init_pixel_array(&mem, &scene);
		printf("init_pixel_array called\n"); // TODO remove
		printf("mem.pixels[540][962].mid.raydir = %f, %f, %f\n", mem.pixels[540][962].mid.ray_dir.x, mem.pixels[540][962].mid.ray_dir.y, mem.pixels[540][962].mid.ray_dir.z); // TODO remove
		check_object_intersection(&scene, &mem.pixels[540][962].mid);
		printf("check_object_intersection called\n"); */  // TODO remove
		



		free_everything(&mem, &scene);
	}
	else
		return (err_return("File not found"));
	return (SUCCESS);
}
