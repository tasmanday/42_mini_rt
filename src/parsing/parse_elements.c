/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:59:55 by atang             #+#    #+#             */
/*   Updated: 2024/11/28 20:36:53 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//int	parse_ambient_light(t_AmbientLight *ambient_light)
int	parse_ambient_light(char **line, t_AmbientLight *ambient_light)
{
	char	*token;
	float	ratio;

	printf(G "Entering" RST " parse_ambient_light()\n\n");
	if (get_next_token(line, &token) == FAILURE)
		warn_err_exit("   No token found", 10);
	ratio = parse_float(&token);
	if (ratio == FAILURE)
		err_exit(10);
	ambient_light->ratio = ratio;
	if (ambient_light->ratio < 0.0f || ambient_light->ratio > 1.0f)
		warn_err_exit("\n   Ambient light ratio out of range (0.0 to 1.0)", 10);
	printf("\n   -> Parsed ratio: %f\n\n", ambient_light->ratio);
	if (parse_rgb(&ambient_light->colour, line) == FAILURE)
		err_exit(10);
	if (get_next_token(line, &token) == SUCCESS)
		warn_err_exit("\n   Error! Excess ambient light value(s)", 10);
	printf(G "   SUCCESS - Ambient Light parsed and added!\n\n");
	printf(RED "Exiting" RST " parse_ambient_light()\n\n");
	printf("---------------------------------------------------------------\n");
	return (SUCCESS);
}

int	parse_camera(char **line, t_Camera *camera)
{
	char	*token;
	int		fov;

	printf(G "Entering" RST " parse_camera()\n\n");
	if (parse_position(&camera->position, line) == FAILURE)
		err_exit(11);
	printf("\n   -> Parsed position: x = %f, y = %f, z = %f\n\n",
		camera->position.x, camera->position.y, camera->position.z);
	if (parse_orientation(&camera->orientation, line) == FAILURE)
		err_exit(11);
	printf("\n   -> Parsed orientation: x = %f, y = %f, z = %f\n\n",
		camera->orientation.x, camera->orientation.y, camera->orientation.z);
	if (get_next_token(line, &token) == FAILURE)
		warn_err_exit("   Error! Failed to get FOV for camera", 11);
	fov = parse_int(&token);
	if (fov == FAILURE)
		err_exit(10);
	camera->fov = fov;
	if (camera->fov < 0 || camera->fov > 180)
		warn_err_exit("\n   Error! FOV out of range (0-180)", 11);
	printf("\n   -> Parsed FOV: %d\n\n", camera->fov);
	if (get_next_token(line, &token) == SUCCESS)
		warn_err_exit("\n   Error! Excess camera value(s)", 11);
	printf(G "   SUCCESS - Camera parsed and added!\n\n");
	printf(RED "Exiting" RST " parse_camera()\n\n");
	printf("---------------------------------------------------------------\n");
	return (SUCCESS);
}

int	parse_light(char **line, t_Light *light)
{
	char	*token;
	float	brightness;

	printf(G "Entering" RST " parse_light()\n\n");
	if (parse_vector3(line, &light->position) == FAILURE)
		warn_err_exit("\n   Error! Failed to get position for light point", 12);
	if (get_next_token(line, &token) == FAILURE)
		warn_err_exit("   No brightness value found", 12);
	brightness = parse_float(&token);
	if (brightness == FAILURE)
		warn_err_exit(" for brightness", 12);
	if (brightness < 0.0f || brightness > 1.0f)
		warn_err_exit("\n   Light brightness ratio out of range (0.0 to 1.0)", 12);
	light->brightness = brightness;
	printf("\n   -> Parsed brightness: %f\n\n", light->brightness);
	if (parse_rgb(&light->colour, line) == FAILURE)
		err_exit(12);
	if (get_next_token(line, &token) == SUCCESS)
		warn_err_exit("\n   Excess light value(s)", 12);
	printf(G "   SUCCESS - Light parsed and added!\n\n");
	printf(RED "Exiting" RST " parse_light()\n\n");
	printf("---------------------------------------------------------------\n");
	return (SUCCESS);
}
/*
// OG parse_camera
int	parse_camera(t_Camera *camera)
{
	char	*token;
	int		fov;

	printf(G "Entering" RST " parse_camera()\n\n");
	if (parse_position(&camera->position, &token) == FAILURE)
		err_exit(11);
	printf("\n   -> Parsed position: x = %f, y = %f, z = %f\n\n",
		camera->position.x, camera->position.y, camera->position.z);
	if (parse_orientation(&camera->orientation, &token) == FAILURE)
		err_exit(11);
	printf("\n   -> Parsed orientation: x = %f, y = %f, z = %f\n\n",
		camera->orientation.x, camera->orientation.y, camera->orientation.z);
	if (get_next_token(&token) == FAILURE)
		warn_err_exit("   Error! Failed to get FOV for camera", 11);
	fov = parse_int(&token);
	if (fov == FAILURE)
		err_exit(10);
	camera->fov = fov;
	if (camera->fov < 0 || camera->fov > 180)
		warn_err_exit("\n   Error! FOV out of range (0-180)", 11);
	printf("\n   -> Parsed FOV: %d\n\n", camera->fov);
	if (get_next_token(&token) == SUCCESS)
		warn_err_exit("\n   Error! Excess camera value(s)", 11);
	printf(G "   SUCCESS - Camera parsed and added!\n\n");
	printf(RED "Exiting" RST " parse_camera()\n\n");
	printf("---------------------------------------------------------------\n");
	return (SUCCESS);
}

// OG parse_light
int	parse_light(t_Light *light)
{
	char	*token;
	float	brightness;

	printf(G "Entering" RST " parse_light()\n\n");
	if (parse_vector3(&light->position) == FAILURE)
		warn_err_exit("\n   Error! Failed to get position for light point", 12);
	if (get_next_token(&token) == FAILURE)
		warn_err_exit("   No brightness value found", 12);
	brightness = parse_float(&token);
	if (brightness == FAILURE)
		warn_err_exit(" for brightness", 12);
	if (brightness < 0.0f || brightness > 1.0f)
		warn_err_exit("\n   Light brightness ratio out of range (0.0 to 1.0)", 12);
	light->brightness = brightness;
	printf("\n   -> Parsed brightness: %f\n\n", light->brightness);
	if (parse_rgb(&light->colour, &token) == FAILURE)
		err_exit(12);
	if (get_next_token(&token) == SUCCESS)
		warn_err_exit("\n   Excess light value(s)", 12);
	printf(G "   SUCCESS - Light parsed and added!\n\n");
	printf(RED "Exiting" RST " parse_light()\n\n");
	printf("---------------------------------------------------------------\n");
	return (SUCCESS);
}
*/
