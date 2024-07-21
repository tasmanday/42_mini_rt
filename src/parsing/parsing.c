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
	// check if there is already an ambient light node (flag in mrt)
	// fill elem struct with relavent data (set A present flag to true)
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
