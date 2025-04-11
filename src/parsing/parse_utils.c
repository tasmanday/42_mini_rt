/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 22:52:53 by atang             #+#    #+#             */
/*   Updated: 2025/02/02 22:14:31 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
			"\n   Error! Invalid character in float in '%s'"RST, *str);
		return (FAILURE);
	}
	*str = end;
	while (**str == ' ' || **str == '\t' || **str == ',')
	{
		(*str)++;
	}
	return (result);
}

int	parse_int(char **str)
{
	char		*end;
	long long	result;

	result = ft_atoi(*str);
	end = *str;
	if (*end == '-' || *end == '+')
		end++;
	while (*end && ft_isdigit(*end))
		end++;
	if (*end != '\0' && !ft_isspace(*end) && *end != ',')
	{
		printf(RED "\n   Error! Invalid character in '%s'" RST, *str);
		return (FAILURE);
	}
	if (*end == ',' || *end == '\0' || *end == ' ' || *end == '\t')
		*str = end + 1;
	else
		*str = end;
	return ((int)result);
}
