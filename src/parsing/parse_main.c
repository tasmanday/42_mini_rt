/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:44:24 by atang             #+#    #+#             */
/*   Updated: 2024/11/25 14:08:26 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_scene_info(t_Scene *scene)
{
	printf(M "---> PRINTING ELEMENTS AND OBJECTS <---\n\n" RST);
	printf(G "Entering" RST " print_ambient_light(), print_camera(), and \
print_light()\n");
	print_ambient_light(&scene->ambient_light);
	print_camera(&scene->camera);
	print_light(&scene->light);
	printf(RED "\nExiting" RST " print_ambient_light(), print_camera(), \
and print_light()\n\n");
	printf("---------------------------------------------------------------\n");
	print_all_objects(scene);
}

int	process_line(char *line, t_Scene *scene)
{
	if (parse_line(line, scene) == FAILURE)
	{
		printf("Error parsing line: %s\n", line);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	parse_rt_file(const char *filename, t_Scene *scene)
{
	int		fd;
	char	*line;
	int		result;

	scene->objects = NULL;
	scene->object_count = 0;
	printf(M "\n---> PARSING ELEMENTS AND OBJECTS <---\n" RST);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nCould not open file: %s\n", filename);
		return (FAILURE);
	}
	result = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			printf(Y "\nLine read: get_next_line returned NULL - EOF or error!\n\n" RST);
			result = 0;
			free(line);
			break ;
		}
		printf(Y "\nLine read: %s" RST, line);
		if (process_line(line, scene) == FAILURE)
			result = 0;
		free(line);
	}
	close(fd);
	print_scene_info(scene);
	return (result);
}

int	parse_line(char *line, t_Scene *scene)
{
	char	*token;

	token = ft_strtok(&line, " \t\n");
	if (!token)
		return (SUCCESS);

	printf(C "\nParsing line with token: %s\n" RST, token);

	if (strcmp(token, "A") == 0)
	{
		if (scene->ambient_light_parsed)
			warn_err_exit("\n   Multiple ambient light definitions", 10);
		scene->ambient_light_parsed = 1;
		//return (parse_ambient_light(&scene->ambient_light));
		return (parse_ambient_light(&line, &scene->ambient_light));
	}
	/*
	else if (strcmp(token, "C") == 0)
	{
		if (scene->camera_parsed)
			warn_err_exit("\n   Multiple camera definitions", 11);
		scene->camera_parsed = 1;
		return (parse_camera(&scene->camera));
	}
	else if (strcmp(token, "L") == 0)
	{
		if (scene->light_parsed)
			warn_err_exit("\n   Multiple light definitions", 12);
		scene->light_parsed = 1;
		return (parse_light(&scene->light));
	}
	else if (strcmp(token, "sp") == 0 || strcmp(token, "pl") == 0 || strcmp(token, "cy") == 0)
	{
		if (scene->object_count >= MAX_OBJECTS)
		{
			printf("Error\nExceeded maximum number of objects\n");
			return (FAILURE);
		}
		if (strcmp(token, "sp") == 0)
			return (parse_sphere(scene));
		else if (strcmp(token, "pl") == 0)
			return (parse_plane(line, scene));
		else if (strcmp(token, "cy") == 0)
			return (parse_cylinder(line, scene));
	}
	*/
	else
	{
		printf(RED "Error\nUnknown identifier: %s\n\n" RST, token);
		return (FAILURE);
	}
	return (SUCCESS);
}
