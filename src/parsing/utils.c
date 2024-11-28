/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:59:30 by atang             #+#    #+#             */
/*   Updated: 2024/11/28 20:38:19 by sentry           ###   ########.fr       */
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

/*
--> WORKING OG get_net_token
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
*/

//adapted for new line parameter
int	get_next_token(char **line, char **token)
{
	if (!line || !*line)
		return (FAILURE);
	*token = ft_strtok(line, " ,\t\n");
	while (*token && **token == '\0')
	{
        *token = ft_strtok(NULL, " \t\n");;
    }
	if (!*token)
	{
		return (FAILURE);
	}
	//*line = NULL; 
	printf("   Token: %s\n", *token);
	return (SUCCESS);
}


char *ft_strtok(char **line, const char *delim)
{
    char *start;
    
    if (line == NULL || *line == NULL)
	{
		//printf("If last == NULL of the content is NULL\n");
		return (NULL);
	}
    while (**line && strchr(delim, **line))
	{
        //printf("Skipping delimiter: '%s'\n", *line);
		(*line)++;
    }
    if (**line == '\0')
	{
		//printf("End of string reached after skipping delimiters\n");
        *line = NULL;
        return (NULL);
    }
    start = *line;
	//printf("\nStart of token: '%s'\n", start);
    while (**line && !strchr(delim, **line)) // find end of token
	{
        (*line)++;
    }
    if (**line)
	{
		//printf("Delimiter found: '%c'\n", **line);
        **line = '\0';
        (*line)++;  // Move past the delimiter
    }
	else
	{
		//printf("End of string reached while parsing token\n");
        *line = NULL;  // No more tokens
    }
	//printf("Returning token: '%s'\n", start);
    return (start);
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
