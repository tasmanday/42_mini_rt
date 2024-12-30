/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:26:47 by atang             #+#    #+#             */
/*   Updated: 2024/11/20 15:30:08 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	file_exists(char *filename)
{
	FILE	*file;

	file = fopen(filename, "r");
	if (file != NULL)
	{
		fclose(file);
		return (1);
	}
	return (0);
}

int	file_status(const char	*filename)
{
	int		fd;
	char	buffer;
	ssize_t	bytes_read;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (err_return("Failed to open file"));
	bytes_read = read(fd, &buffer, 1);
	close(fd);
	if (bytes_read == -1)
		return (err_return("Failed to read file"));
	if (bytes_read == 0)
		return (err_return("File is empty"));
	return (SUCCESS);
}

int	filename_error(char	*filename)
{
	size_t	filename_len;

	filename_len = ft_strlen(filename);
	if (ft_strncmp(&filename[filename_len - 3], ".rt", 3))
		return (1);
	return (0);
}
