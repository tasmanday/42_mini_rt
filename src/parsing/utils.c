/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:59:30 by atang             #+#    #+#             */
/*   Updated: 2024/11/08 19:34:49 by atang            ###   ########.fr       */
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
	while (*token && **token == '\0') // Skip empty tokens if any
    {
        *token = strtok(NULL, " \t,");
    }

	if (!*token)
	{
		return (FAILURE);
	}
	printf("   Token: %s\n", *token);
	return (SUCCESS);
}


/*
int get_next_token(char **token, char **input_buffer)
{
    // Initialize the tokenizer with the input buffer on the first call
    if (*token == NULL) {
        *token = strtok(*input_buffer, " \t,");
    } else {
        *token = strtok(NULL, " \t,");
    }

    // Check if a token was found
    if (!*token)
    {
        return FAILURE;
    }

    // Trim any leading or trailing whitespace from the token
    while (isspace((unsigned char)**token)) (*token)++;  // Trim leading
    char *end = *token + strlen(*token) - 1;  // Set end to the last character
    while (end > *token && isspace((unsigned char)*end)) end--;  // Trim trailing

    // Null-terminate the token
    *(end + 1) = '\0';

    printf("   Token: %s\n", *token);
    return SUCCESS;
}
*/


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

char *ft_strtok(char *str, const char *delim)
{
    static char *last = NULL;
    char *start;
    char *current;

    // If no string is passed, continue from the last one
    if (str == NULL)
        str = last;

    // Skip leading delimiters (spaces, tabs, etc.)
    while (*str && strchr(delim, *str))
        str++;

    // If we've reached the end of the string
    if (*str == '\0')
        return NULL;

    // Set the start of the token
    start = str;

    // Move through the string to find the first delimiter or end of string
    current = str;
    while (*current && !strchr(delim, *current))
    {
        current++;
    }

    // Null-terminate the token
    if (*current != '\0')
    {
        *current = '\0'; // End the token
        last = current + 1; // Move the pointer to the next part of the string
    }
    else
    {
        last = current; // End of string reached
    }

    // Trim unwanted newline or carriage return characters from the token
    char *token_end = start + strlen(start) - 1;
    while (token_end >= start && (*token_end == '\n' || *token_end == '\r' || isspace((unsigned char)*token_end)))
    {
        *token_end = '\0'; // Null-terminate at the trimmed point
        token_end--;
    }

    return start;
}

