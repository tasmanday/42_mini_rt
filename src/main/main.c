/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:17:07 by tday              #+#    #+#             */
/*   Updated: 2024/07/21 15:58:12 by tday             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	main(int argc, char **argv)
{
	t_mrt	*mrt;

	init_mrt(mrt);

	
	// uncomment later when we need to deal with minilibx
	/* t_data	data;

	init_window(&data);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.width, data.height, "mini_rt");
	init_img(&data);

	mlx_hook(data.win, ON_DESTROY, 0, close_window, &data);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_loop_hook(data.mlx, loop_function, &data);

	mlx_loop(data.mlx); */
	return (0);
}
