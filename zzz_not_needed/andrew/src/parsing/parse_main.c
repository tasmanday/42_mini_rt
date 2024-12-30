/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:44:24 by atang             #+#    #+#             */
/*   Updated: 2024/10/19 14:33:21 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	parse_rt_file()
	Manages file operations and calls parse_line() for each line read from the 
	file
*/

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
		return (0);
	}
	scene->object_count = 0;
	result = 1;
	while (1)
	{
		line = NULL;
		if (get_next_line(fd, &line) == NULL)
		{
			printf(Y "\nLine read: get_next_line returned NULL - EOF or error!\n\n" RST);
			result = 0;
			free(line);
			break ;
		}
		printf(Y "\nLine read: %s" RST, line);
		if (!parse_line(line, scene))
		{
			result = 0;
			printf("Error parsing line: %s\n", line);
		}
		free(line);
		if (line == NULL)
			break ;
	}
	close(fd);
	printf(M "---> PRINTING ELEMENTS AND OBJECTS <---\n\n" RST);
	printf(G "Entering" RST " print_ambient_light(),\
	print_camera(), and print_light()\n");
	print_ambient_light(&scene->ambient_light);
	print_camera(&scene->camera);
	print_light(&scene->light);
	printf(RED "\nExiting" RST " print_ambient_light(), print_camera(), and print_light()\n\n");
	printf("---------------------------------------------------------------\n");
	print_all_objects(scene);
	return (result);
}

/*
	parse_line()
	Handles the parsing of scene elements and objects, checking for valid
	idetifiers and managing object count
*/

int	parse_line(char *line, t_Scene *scene)
{
	char	*token;

	token = strtok(line, " \t\n");
	if (!token)
		return (1);
	printf(C "Parsing line with token: %s\n" RST, token);
	if (strcmp(token, "A") == 0)
		return (parse_ambient_light(line, &scene->ambient_light));
	else if (strcmp(token, "C") == 0)
		return (parse_camera(line, &scene->camera));
	else if (strcmp(token, "L") == 0)
		return (parse_light(line, &scene->light));
	if (strcmp(token, "sp") == 0 || strcmp(token, "pl") == 0
		|| strcmp(token, "cy") == 0)
	{
		if (scene->object_count >= MAX_OBJECTS)
		{
			printf("Error\nExceeded maximum number of objects\n");
			return (0);
		}
		if (strcmp(token, "sp") == 0)
			return (parse_sphere(line, scene));
		else if (strcmp(token, "pl") == 0)
			return (parse_plane(line, scene));
		else if (strcmp(token, "cy") == 0)
			return (parse_cylinder(line, scene));
	}
	else
	{
		printf(RED "Error\nUnknown identifier: %s\n\n" RST, token);
		return (0);
	}
	return (0);
}
