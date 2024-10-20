/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:59:55 by atang             #+#    #+#             */
/*   Updated: 2024/10/20 13:48:07 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_ambient_light(char *line, t_AmbientLight *ambient_light)
{
	char	*token;
	float	ratio;

	(void) line;
	printf(G "Entering" RST " parse_ambient_light()\n\n");
	if (!get_next_token(&token))
		return (0);
	ratio = parse_float(&token);
	if (!ratio)
		err_exit(0);
	ambient_light->ratio = ratio;
	if (ambient_light->ratio < 0.0f || ambient_light->ratio > 1.0f)
		err_exit(5);
	printf("   Parsed ratio: %f\n", ambient_light->ratio);
	if (!get_next_token(&token))
		err_exit(3);
	parse_colour(token, &ambient_light->colour);
	printf(G "   SUCCESS - Ambient Light parsed and added!\n\n");
	printf(RED "Exiting" RST " parse_ambient_light()\n\n");
	printf("---------------------------------------------------------------\n");
	return (SUCCESS);
}

int	parse_camera(char *line, t_Camera *camera)
{
	char	*token;

	(void) line;
	printf(G "Entering" RST " parse_camera()\n\n");
	if (!get_next_token(&token))
		return (printf("   Failed to get X position for camera\n"), 0);
	camera->position.x = atof(token);
	if (!get_next_token(&token))
		return (printf("   Failed to get Y position for camera\n"), 0);
	camera->position.y = atof(token);
	if (!get_next_token(&token))
		return (printf("   Failed to get Z position for camera\n"), 0);
	camera->position.z = atof(token);
	printf("   Parsed position: x = %f, y = %f, z = %f\n", camera->position.x,
		camera->position.y, camera->position.z);
	if (!get_next_token(&token))
		return (printf("   Failed to get X orientation for camera\n"), 0);
	camera->orientation.x = atof(token);
	if (!get_next_token(&token))
		return (printf("   Failed to get Y orientation for camera\n"), 0);
	camera->orientation.y = atof(token);
	if (!get_next_token(&token))
		return (printf("   Failed to get Z orientation for camera\n"), 0);
	camera->orientation.z = atof(token);
	printf("   Parsed orientation: x = %f, y = %f, z = %f\n",
		camera->orientation.x, camera->orientation.y, camera->orientation.z);
	if (!get_next_token(&token))
		return (printf("   Failed to get FOV for camera\n"), 0);
	camera->fov = atof(token);
	printf("   Parsed FOV: %f\n", camera->fov);
	if (camera->fov < 0 || camera->fov > 180)
	//	err_exit("Camera FOV out of range (0 to 180)");
		err_exit(7);
	printf(G "   SUCCESS - Camera parsed and added!\n\n");
	printf(RED "Exiting" RST " parse_camera()\n\n");
	printf("---------------------------------------------------------------\n");
	return (SUCCESS);
}

int	parse_light(char *line, t_Light *light)
{
	char	*token;

	(void) line;
	printf(G "Entering" RST " parse_light()\n\n");
	if (!get_next_token(&token))
		return (0);
	parse_vector3(token, &light->position);
	if (!get_next_token(&token))
		return (0);
	light->brightness = parse_float(&token);
	if (light->brightness < 0.0f || light->brightness > 1.0f)
		//err_exit("Light brightness ratio out of range (0.0 to 1.0)");
		err_exit(6);
	if (!get_next_token(&token))
		return (0);
	parse_colour(token, &light->colour);
	printf(G "   SUCCESS - Light parsed and added!\n\n");
	printf(RED "Exiting" RST " parse_light()\n\n");
	printf("---------------------------------------------------------------\n");
	return (1);
}
