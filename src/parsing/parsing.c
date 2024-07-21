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
