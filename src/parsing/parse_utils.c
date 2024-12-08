/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:24:03 by atang             #+#    #+#             */
/*   Updated: 2024/12/07 22:44:39 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int parse_vector3(char **line, t_Vector3 *vec)
{
    char    *token;
    float   *coords[3];
    int     i;

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

static int validate_rgb(char *token)
{
    int i;

    i = 0;
    if (token[i] == '-')
        i++;
    while (token[i] != '\0')
    {
        if (!ft_isdigit((unsigned char)token[i]))
            return (FAILURE);
        i++;
    }
    return (SUCCESS);
}

int parse_rgb(t_Colour *colour, char **line)
{
    int     i;
    int     value;
    char    *token;
    int     *components[3];

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
            return print_error_and_return("RGB value contains \
non-numeric characters", token);
        value = ft_atoi(token);
        if (value < 0 || value > 255)
            return (print_error_and_return("RGB value out of range (0-255)", token));
        *components[i] = value;
        i++;
    }
    return (SUCCESS);
}

int parse_position(t_Vector3 *position, char **line)
{
    char    *endptr;
    int     i;
    float   *coords[3];
    char    *token;

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
        *coords[i] = strtof(token, &endptr);
        if (*endptr != '\0')
        {
            printf(RED"\n   Error! Invalid value for x/y/z position"RST);
            return (FAILURE);
        }
        i++;
    }
    return (SUCCESS);
}

int parse_orientation(t_Vector3 *orientation, char **line)
{
    char    *endptr;
    int     i;
    float   *coords[3];
    char    *token;

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
