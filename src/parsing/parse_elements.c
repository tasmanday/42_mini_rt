/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:59:55 by atang             #+#    #+#             */
/*   Updated: 2024/11/02 17:57:55 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_ambient_light(t_AmbientLight *ambient_light)
{
	char	*token;
	float	ratio;

	printf(G "Entering" RST " parse_ambient_light()\n\n");
	if (get_next_token(&token) == FAILURE)
		warn_err_exit("No token found", 1);
	ratio = parse_float(&token);
	if (ratio == FAILURE)
		err_exit(1);
	ambient_light->ratio = ratio;
	if (ambient_light->ratio < 0.0f || ambient_light->ratio > 1.0f)
		warn_err_exit("Ambient light ratio out of range (0.0 to 1.0)", 1);
	printf("   -> Parsed ratio: %f\n", ambient_light->ratio);
	parse_rgb(&ambient_light->colour, &token);
	printf("   -> Parsed colour: R = %d, G = %d, B = %d\n",
		ambient_light->colour.r, ambient_light->colour.g,
		ambient_light->colour.b);
	if (get_next_token(&token) == SUCCESS)
		warn_err_exit("Excess ambient light values", 1);
	printf(G "   SUCCESS - Ambient Light parsed and added!\n\n");
	printf(RED "Exiting" RST " parse_ambient_light()\n\n");
	printf("---------------------------------------------------------------\n");
	return (SUCCESS);
}

int	parse_camera(t_Camera *camera)
{
	char	*token;

	printf(G "Entering" RST " parse_camera()\n\n");
	if (parse_position(&camera->position, &token) == FAILURE)
		err_exit(2);
	printf("   -> Parsed position: x = %f, y = %f, z = %f\n",
		camera->position.x, camera->position.y, camera->position.z);
	if (parse_orientation(&camera->orientation, &token) == FAILURE)
		err_exit(2);
	printf("   -> Parsed orientation: x = %f, y = %f, z = %f\n",
		camera->orientation.x, camera->orientation.y, camera->orientation.z);
	if (get_next_token(&token) == FAILURE)
		return (printf("   Failed to get FOV for camera\n"), 0);
	camera->fov = atof(token);
	printf("   -> Parsed FOV: %f\n", camera->fov);
	if (camera->fov < 0 || camera->fov > 180)
		err_exit(7);
	printf(G "   SUCCESS - Camera parsed and added!\n\n");
	printf(RED "Exiting" RST " parse_camera()\n\n");
	printf("---------------------------------------------------------------\n");
	return (SUCCESS);
}

int	parse_light(t_Light *light)
{
	char	*token;

	printf(G "Entering" RST " parse_light()\n\n");
	if (parse_vector3(&light->position) == FAILURE)
		err_exit(3);
	if (get_next_token(&token) == FAILURE)
		warn_err_exit("No token found", 3);
	light->brightness = parse_float(&token);
	if (light->brightness < 0.0f || light->brightness > 1.0f)
		warn_err_exit("Light brightness ratio out of range (0.0 to 1.0)", 3);
	printf("   -> Parsed brightness: %f\n", light->brightness);
	if (parse_rgb(&light->colour, &token) != SUCCESS)
		return (FAILURE);
	printf("   -> Parsed colour: R = %d, G = %d, B = %d\n", light->colour.r,
		light->colour.g, light->colour.b);
	if (get_next_token(&token) == SUCCESS)
		warn_err_exit("Excess light values", 3);
	printf(G "   SUCCESS - Light parsed and added!\n\n");
	printf(RED "Exiting" RST " parse_light()\n\n");
	printf("---------------------------------------------------------------\n");
	return (SUCCESS);
}
