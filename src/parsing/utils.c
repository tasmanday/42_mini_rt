/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:59:30 by atang             #+#    #+#             */
/*   Updated: 2025/02/02 22:29:31 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	u1;
	unsigned char	u2;

	while (n > 0)
	{
		if (*s1 != *s2)
		{
			u1 = (unsigned char)*s1;
			u2 = (unsigned char)*s2;
			return (u1 - u2);
		}
		if (*s1 == '\0' && *s2 == '\0')
		{
			break ;
		}
		s1++;
		s2++;
		n--;
	}
	return (0);
}

float	ft_strtof(const char *str, char **endptr)
{
	float	result;
	int		sign;
	float	decimal;

	result = 0.0f;
	sign = 1;
	decimal = 0.1f;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		result = result * 10.0f + (*str++ - '0');
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			result += (*str++ - '0') * decimal;
			decimal *= 0.1f;
		}
	}
	if (endptr)
		*endptr = (char *)str;
	return (result * sign);
}

int	get_next_token(char **line, char **token)
{
	if (!line || !*line)
		return (FAILURE);
	*token = ft_strtok(line, " ,\t\n");
	while (*token && **token == '\0')
	{
		*token = ft_strtok(NULL, " \t\n");
	}
	if (!*token)
	{
		return (FAILURE);
	}
	printf("   Token: %s\n", *token);
	return (SUCCESS);
}

char	*ft_strtok(char **line, const char *delim)
{
	char	*start;

	if (line == NULL || *line == NULL)
	{
		return (NULL);
	}
	while (**line && ft_strchr(delim, **line))
		(*line)++;
	if (**line == '\0')
	{
		*line = NULL;
		return (NULL);
	}
	start = *line;
	while (**line && !ft_strchr(delim, **line))
		(*line)++;
	if (**line)
	{
		**line = '\0';
		(*line)++;
	}
	else
		*line = NULL;
	return (start);
}
