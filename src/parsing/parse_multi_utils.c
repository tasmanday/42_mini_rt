/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_multi_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 22:52:53 by atang             #+#    #+#             */
/*   Updated: 2025/01/18 16:31:59 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_vector3(char **line, t_Vector3 *vec)
{
	char	*token;
	float	*coords[3];
	int		i;

	coords[0] = &vec->x;
	coords[1] = &vec->y;
	coords[2] = &vec->z;
	i = 0;
	while (i < 3)
	{
		if (get_next_token(line, &token) == FAILURE)
		{
			return (FAILURE);
		}
		*coords[i] = parse_float(&token);
		if (*coords[i] == FAILURE)
		{
			return (FAILURE);
		}
		i++;
	}
	printf("\n   -> Parsed vector: x = %f, y = %f, z = %f\n\n",
		vec->x, vec->y, vec->z);
	return (SUCCESS);
}

static int	validate_rgb(char *token)
{
	if (!token)
		return (FAILURE);
	while (*token && (*token == ' ' || *token == '\t'
			|| *token == '\r' || *token == '\n'))
		token++;
	if (*token == '-')
		token++;
	if (*token == '\0')
		return (FAILURE);
	while (*token && *token != ' ' && *token != '\t' && *token
		!= '\r' && *token != '\n')
	{
		if (!ft_isdigit((unsigned char)*token))
			return (FAILURE);
		token++;
	}
	while (*token && (*token == ' ' || *token == '\t' || *token == '\r'
			|| *token == '\n'))
		token++;
	if (*token == '\0')
	{
		return (SUCCESS);
	}
	return (FAILURE);
}

int	parse_rgb(t_Colour4 *colour, char **line)
{
	int		i;
	int		value;
	char	*token;
	float	*components[3];

	components[0] = &colour->r;
	components[1] = &colour->g;
	components[2] = &colour->b;
	i = 0;
	while (i < 3)
	{
		if (get_next_token(line, &token) == FAILURE || token == NULL)
			return (print_error_and_return(
					"No more tokens found for RGB values (needs 3)", NULL));
		if (validate_rgb(token) == FAILURE)
			return (print_error_and_return("RGB value contains \
	non-numeric characters", token));
		value = ft_atoi(token);
		if (value < 0 || value > 255)
			return (print_error_and_return("RGB value out of range (0-255)",
					token));
		*components[i] = value / 255.0f;
		i++;
	}
	colour->a = 1.0f;
	return (SUCCESS);
}

int	parse_position(t_Vector3 *position, char **line)
{
	char	*endptr;
	int		i;
	float	*coords[3];
	char	*token;

	i = 0;
	coords[0] = &position->x;
	coords[1] = &position->y;
	coords[2] = &position->z;
	while (i < 3)
	{
		if (get_next_token(line, &token) == FAILURE)
		{
			printf(RED"\n   Error! Failed to get x/y/z position"RST);
			return (FAILURE);
		}
		*coords[i] = ft_strtof(token, &endptr);
		if (*endptr != '\0')
		{
			printf(RED"\n   Error! Invalid value for x/y/z position"RST);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	parse_orientation(t_Vector3 *orientation, char **line)
{
	char	*endptr;
	int		i;
	float	*coords[3];
	char	*token;

	i = 0;
	coords[0] = &orientation->x;
	coords[1] = &orientation->y;
	coords[2] = &orientation->z;
	while (i < 3)
	{
		if (get_next_token(line, &token) == FAILURE)
			return (print_error_and_return("Failed to get x/y/z \
	orientation", NULL));
		*coords[i] = strtof(token, &endptr);
		if (*endptr != '\0')
			return (print_error_and_return("Invalid value for x/y/z \
	orientation", token));
		if (*coords[i] < -1.0f || *coords[i] > 1.0f)
			return (print_error_and_return("Orientation value out of range \
	(-1, 1)", NULL));
		i++;
	}
	return (SUCCESS);
}
