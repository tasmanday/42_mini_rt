/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:24:03 by atang             #+#    #+#             */
/*   Updated: 2024/11/02 19:03:26 by atang            ###   ########.fr       */
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
			return (FAILURE);
		*coords[i] = parse_float(&token);
		if (*coords[i] == FAILURE)
			return (FAILURE);
		i++;
	}
	printf("   Parsed vector: x = %f, y = %f, z = %f\n",
		vec->x, vec->y, vec->z);
	return (SUCCESS);
}

int	parse_rgb(t_Colour *colour, char **token)
{
	int	i;
	int	value;

	i = 0;
	while (i < 3)
	{
		if (get_next_token(token) == FAILURE || *token == NULL)
			warn_err_exit("No more tokens found for RGB values", 1);
		value = atoi(*token);
		if (value < 0 || value > 255)
		{
			warn_err_exit("RGB value out of range (0-255)", 1);
		}
		if (i == 0)
			colour->r = value;
		else if (i == 1)
			colour->g = value;
		else if (i == 2)
			colour->b = value;
		i++;
	}
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
			printf("   Failed to get x/y/z position\n");
			return (FAILURE);
		}
		*coords[i] = strtof(*token, &endptr);
		if (*endptr != '\0')
		{
			printf("   Invalid value for x/y/z position\n");
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
			printf("   Failed to get x/y/z orientation\n");
			return (FAILURE);
		}
		*coords[i] = strtof(*token, &endptr);
		if (*endptr != '\0')
		{
			printf("   Invalid value for x/y/z orientation\n");
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
