/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:59:30 by atang             #+#    #+#             */
/*   Updated: 2024/11/03 15:55:14 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

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

int	get_next_token(char **token)
{
	*token = strtok(NULL, " \t,");
	if (!*token)
	{
		return (FAILURE);
	}
	printf("   Token: %s\n", *token);
	return (SUCCESS);
}

float	parse_float(char **str)
{
	char	*end;
	float	result;

	while (**str == ' ' || **str == '\t' || **str == ',')
	{
		(*str)++;
	}
	result = strtof(*str, &end);
	if (end == *str)
	{
		printf(RED "\n   Error! No valid float found in '%s'"RST, *str);
		return (FAILURE);
	}
	if (*end != '\0' && !ft_isspace(*end) && *end != ',')
	{
		printf(RED
			"\n   Error! Invalid characters in float in: '%s'"RST, *str);
		return (FAILURE);
	}
	*str = end;
	while (**str == ' ' || **str == '\t' || **str == ',')
	{
		(*str)++;
	}
	return (result);
}

int	parse_int(char	**str)
{
	char	*end;
	int		result;

	result = (int)strtol(*str, &end, 10);
	if (end == *str)
		return (0);
	if (*end == ',' || *end == '\0' || *end == ' ' || *end == '\t')
		*str = end + 1;
	else
		*str = end;
	return (result);
}
