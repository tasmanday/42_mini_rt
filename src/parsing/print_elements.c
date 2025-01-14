/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 22:48:40 by atang             #+#    #+#             */
/*   Updated: 2025/01/07 22:48:42 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_ambient_light(t_AmbientLight *ambient)
{
	printf(B "\n   Ambient Light:\n" RST);
	printf("      Ratio: %f\n", ambient->ratio);
	printf("      Colour: %f, %f, %f\n", ambient->colour.r,
		ambient->colour.g, ambient->colour.b);
}

void	print_camera(const t_Camera *camera)
{
	printf(Y "\n   Camera:\n" RST);
	printf("      Position: %f, %f, %f\n", camera->position.x,
		camera->position.y, camera->position.z);
	printf("      Orientation: %f, %f, %f\n", camera->orientation.x,
		camera->orientation.y, camera->orientation.z);
	printf("      FOV: %d\n", camera->fov);
}

void	print_light(const t_Light *light)
{
	printf(C "\n   Light:\n" RST);
	printf("      Position: %f, %f, %f\n", light->position.x, light->position.y,
		light->position.z);
	printf("      Brightness: %f\n", light->brightness);
	printf("      Colour: %f, %f, %f\n", light->colour.r, light->colour.g,
		light->colour.b);
}
