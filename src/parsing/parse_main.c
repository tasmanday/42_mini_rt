/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:44:24 by atang             #+#    #+#             */
/*   Updated: 2024/12/08 11:40:12 by sentry           ###   ########.fr       */
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

/*
--> OG parse_rt_file
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
			printf(Y "\nLine read: get_next_line returned NULL \
				- EOF or error!\n\n" RST);
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
		return (print_error_and_return("Error: Could not open file", filename));
	result = SUCCESS;
	while ((line = get_next_line(fd)))
	{
		printf(Y "\nLine read: %s" RST, line);
		if (process_line(line, scene) == FAILURE)
			result = FAILURE;
		free(line);
	}
	if (line == NULL && errno != 0)
		return (print_error_and_return("Error: Failed to read line from file",
				filename));
	printf(Y "\nEnd of file reached successfully.\n\n" RST);
	close(fd);
	print_scene_info(scene);
	return (result);
}

static int	check_multiple_definitions(const char *token, int *flag,
	int error_code)
{
	(void) token;
	if (*flag)
		warn_err_exit("\n   Multiple definitions detected", error_code);
	*flag = 1;
	return (SUCCESS);
}

static int	parse_object( const char *token, char **line, t_Scene *scene)
{
	if (scene->object_count >= MAX_OBJECTS)
	{
		printf("Error\nExceeded maximum number of objects\n");
		return (FAILURE);
	}
	if (ft_strcmp(token, "sp") == 0)
		return (parse_sphere(line, scene));
	else if (ft_strcmp(token, "pl") == 0)
		return (parse_plane(line, scene));
	else if (ft_strcmp(token, "cy") == 0)
		return (parse_cylinder(line, scene));
	return (FAILURE);
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
		if (check_multiple_definitions(token, &scene->ambient_light_parsed, 10) == FAILURE)
			return (FAILURE);
		return (parse_ambient_light(&line, &scene->ambient_light));
	}
	else if (strcmp(token, "C") == 0)
	{
		if (check_multiple_definitions(token, &scene->camera_parsed, 11) == FAILURE)
			return (FAILURE);
		return (parse_camera(&line, &scene->camera));
	}
	else if (strcmp(token, "L") == 0)
	{
		if (check_multiple_definitions(token, &scene->light_parsed, 12) == FAILURE)
			return (FAILURE);
		return (parse_light(&line, &scene->light));
	}
	else if (strcmp(token, "sp") == 0 || strcmp(token, "pl") == 0 || strcmp(token, "cy") == 0)
		return (parse_object(token, &line, scene));
	else
	{
		printf(RED "Error\nUnknown identifier: %s\n\n" RST, token);
		return (FAILURE);
	}
	return (SUCCESS);
}
