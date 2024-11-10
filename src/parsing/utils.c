/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:59:30 by atang             #+#    #+#             */
/*   Updated: 2024/11/10 11:39:54 by sentry           ###   ########.fr       */
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
	*token = strtok(NULL, " ,\t\n");
	while (*token && **token == '\0') // Skip empty tokens if any
    {
        *token = strtok(NULL, " \t\n");
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
		//exit(1);
	}
	*str = end;
	while (**str == ' ' || **str == '\t' || **str == ',')
	{
		(*str)++;
	}
	return (result);
}

/*
int	parse_int(char	**str)
{
	char		*end;
	long long	result;

	result = ft_atoi(*str);
	end = *str;
	while (*end && (ft_isdigit(*end))
	{
		end++;
	}
	if (end == *str)
	{
		printf(RED "\n   Error! No valid int found in '%s'" RST, *str);
		return (FAILURE);
	}
	if (*end == ',' || *end == '\0' || *end == ' ' || *end == '\t')
		*str = end + 1;
	else
		*str = end;
	if (*end != '\0' && !ft_isspace(*end) && *end != ',')
	{
		printf(RED "\n   Error! Invalid character in int in '%s'" RST, *str);
		return (FAILURE);
	}
	return ((int)result);
}
*/

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
		printf(RED "\n   Error! Invalid character in '%s' when parsing int" RST, *str);
		return (FAILURE);
	}
	if (*end == ',' || *end == '\0' || *end == ' ' || *end == '\t')
		*str = end + 1;
	else
		*str = end;
	return ((int)result);
}
