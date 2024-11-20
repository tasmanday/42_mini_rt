/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:24:03 by atang             #+#    #+#             */
/*   Updated: 2024/11/20 11:33:39 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_vector3(t_Vector3 *vec)
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
		if (get_next_token(&token) == FAILURE)
		{
			return (FAILURE);
		}
		*coords[i] = parse_float(&token);
		if (*coords[i] == FAILURE)
		{
			printf(RED" when parsing vector"RST);
			return (FAILURE);
		}
		i++;
	}
	printf("\n   -> Parsed vector: x = %f, y = %f, z = %f\n\n",
		vec->x, vec->y, vec->z);
	return (SUCCESS);
}

int	parse_rgb(t_Colour *colour, char **token)
{
	int	i;
	int	j;
	int	value;

	i = 0;
	while (i < 3)
	{
		if (get_next_token(token) == FAILURE || *token == NULL)
		{
			printf(RED"\n   No more tokens found for RGB values (needs 3)"RST);
			return (FAILURE);
		}
		j = 0;
		while ((*token)[j] != '\0')
		{
			if (!ft_isdigit((unsigned char)(*token)[j]))
			{
				printf(RED "\n   Error! '%s' contains non-numeric characters for \
RGB" RST, *token);
				return (FAILURE);
			}
			j++;
		}
		value = ft_atoi(*token);
		if (value < 0 || value > 255)
		{
			if (value < 0 || value > 255)
			{
				printf(RED"\n   Error! RGB value out of range (0-255)"RST);
				return (FAILURE);
			}
			/*
			else if (!value)
			{
				printf(RED"\n   Error! Conversion of RGB value failed"RST);
				return (FAILURE);
			}
			*/
		}
		if (i == 0)
			colour->r = value;
		else if (i == 1)
			colour->g = value;
		else if (i == 2)
			colour->b = value;
		i++;
	}
	printf("\n   -> Parsed colour: R = %d, G = %d, B = %d\n\n", colour->r,
		colour->g, colour->b);
	return (SUCCESS);
}

int	parse_position(t_Vector3 *position, char **token)
{
	char	*endptr;
	int		i;
	float	*coords[3];

	i = 0;
	coords[0] = &position->x;
	coords[1] = &position->y;
	coords[2] = &position->z;
	while (i < 3)
	{
		if (get_next_token(token) == FAILURE)
		{
			printf(RED"\n   Error! Failed to get x/y/z position"RST);
			return (FAILURE);
		}
		*coords[i] = strtof(*token, &endptr);
		if (*endptr != '\0')
		{
			printf(RED"\n   Error! Invalid value for x/y/z position"RST);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	parse_orientation(t_Vector3 *orientation, char **token)
{
	char	*endptr;
	int		i;
	float	*coords[3];

	i = 0;
	coords[0] = &orientation->x;
	coords[1] = &orientation->y;
	coords[2] = &orientation->z;
	while (i < 3)
	{
		if (get_next_token(token) == FAILURE)
		{
			printf(RED"\n   Failed to get x/y/z orientation"RST);
			return (FAILURE);
		}
		*coords[i] = strtof(*token, &endptr);
		if (*endptr != '\0')
		{
			printf(RED"\n   Invalid value for x/y/z orientation: \
'%s'"RST, *token);
			return (FAILURE);
		}
		if (*coords[i] < -1.0f || *coords[i] > 1.0f)
		{
			printf(RED"\n   Orientation value out of range (-1, 1)"RST);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
