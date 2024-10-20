/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:24:03 by atang             #+#    #+#             */
/*   Updated: 2024/10/19 11:01:59 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	parse_float()
	Converts a str to float and updates the string pointer to point at the next 
	part of the string after the converted number
*/

float	parse_float(char **str)
{
	char	*end;
	float	result;

	result = strtof(*str, &end);
	if (end == *str)
	{
		printf("   Warning: No valid float found in '%s'\n", *str);
		return (0.0f);
	}
	*str = end;
	while (**str == ' ' || **str == '\t' || **str == ',')
		(*str)++;
	return (result);
}

/*
	parse_int()
	Converts a str to int and updates the string pointer to point at the next 
	part of the string after the converted number
*/

int	parse_int(char	**str)
{
	char	*end;
	int		result;

	result = (int)strtol(*str, &end, 10);
	if (end == *str)
		return (0);
	if (*end == ',' || *end == '\0')
		*str = end + 1;
	else
		*str = end;
	return (result);
}

/*
	parse_vector3()
	Converts 3 floating-point numbers from a str and assigns them to the Vector3 
	structure's x, y, and z components. Each call to parse_float updates the str 
	pointer to point at the next part of the string
*/

int	parse_vector3(char *str, t_Vector3 *vec)
{
	printf("   Parsing vector from: %s\n", str);
	vec->x = parse_float(&str);
	vec->y = parse_float(&str);
	vec->z = parse_float(&str);
	printf("   Parsed vector: x = %f, y = %f, z = %f\n", vec->x,
		vec->y, vec->z);
	return (1);
}
/*
	parse_colour()
	Converts 3 int numbers from a str and assigns them to the Colour structure's 
	r, g, and b components
*/

int	parse_colour(char *str, t_Colour *colour)
{
	colour->r = parse_int(&str);
	colour->g = parse_int(&str);
	colour->b = parse_int(&str);
	if (colour->r < 0 || colour->r > 255
		|| colour->g < 0 || colour->g > 255
		|| colour->b < 0 || colour->b > 255)
	{
		//printf(RED "Error: Colour values out of bounds (0-255).\n" RST);
		//return (0);
		err_exit(0);
	}
	printf("   Parsed colour: R = %d, G = %d, B = %d\n", colour->r,
		colour->g, colour->b);
	return (1);
}

int	get_next_token(char **token)
{
	*token = strtok(NULL, " \t");
	if (!*token)
		return (0);
	return (1);
}
