/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:29:18 by atang             #+#    #+#             */
/*   Updated: 2024/10/19 10:14:15 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_Scene	scene;

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
		parse_rt_file(argv[1], &scene);
		initialise_data(&scene);
		printf(M "\n---> WINDOW OPENED <---\n\n" RST);
		mlx_key_hook(scene.mlx.win_ptr, deal_key, &scene);
		mlx_hook(scene.mlx.win_ptr, 17, 0, close_button_hook, &scene);
		mlx_loop(scene.mlx.mlx_ptr);
	}
	else
		return (err_return("File not found"));
	return (SUCCESS);
}
