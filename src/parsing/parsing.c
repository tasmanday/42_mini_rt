/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:32:44 by tday              #+#    #+#             */
/*   Updated: 2024/07/21 17:14:40 by tday             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	parse_ambient_light(t_mrt *mrt, char **elem_array)
{
	t_amb	*ambient_light;
	// check if there is already an ambient light node (flag in mrt)
	if (mrt->amb->id)
		error_exit("invlaid scene file: multiple ambient lights"); // need to make free_everything function and a version of error_exit that frees everything before exiting
	else if (sizeof(elem_array)/sizeof(elem_array[0]) != 3)
		error_exit("invlaid scene file: incorrect number of parameters in \
		ambient light element");
	else
	{ // fill elem struct with relavent data
		ambient_light = safe_calloc(1, sizeof(t_amb), \
			"parse_ambient_light: malloc error");
		ambient_light->id = ft_strdup(elem_array[0]);
		ambient_light->ratio = ratio_atof(elem_array[1], "parse_ambient_light"); // atof with check that result is within range 0.0 - 1.0
		ambient_light->rgb = rgb_atoi(elem_array[2], "parse_ambient_light"); // split rgb param, atoi results, check results are within range 0 - 255, 
	}
	// add node to linked list with elem struct as data
}

void	process_array_params(t_mrt *mrt, char **elem_array)
{
	if (!ft_strcmp(elem_array[0], "A"))
		parse_ambient_light(mrt, elem_array);
	else if (!ft_strcmp(elem_array[0], "L"))
		parse_light(mrt, elem_array);
	else if (!ft_strcmp(elem_array[0], "C"))
		parse_camera(mrt, elem_array);
	else if (!ft_strcmp(elem_array[0], "sp"))
		parse_sphere(mrt, elem_array);
	else if (!ft_strcmp(elem_array[0], "pl"))
		parse_plane(mrt, elem_array);
	else if (!ft_strcmp(elem_array[0], "cy"))
		parse_cylinder(mrt, elem_array);
	else
	{
		perror("invalid ID in scene file");
		exit(EXIT_FAILURE);
	}
}

void	parse_line(t_mrt *mrt, char *line)
{
	char	**elem_array;

	elem_array = ft_split_whitespace(line);
	process_array_params(mrt, elem_array);
	free_array(elem_array);
}

void	parse_file(t_mrt *mrt, char **argv)
{
	int		fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror("parse_file open failed"), (NULL));
	while ((line = get_next_line(fd)) != NULL)
	{
		parse_line(mrt, line);
		free(line);
	}
	close(fd);
}
