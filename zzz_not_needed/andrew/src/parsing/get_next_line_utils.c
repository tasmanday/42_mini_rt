/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:04:20 by atang             #+#    #+#             */
/*   Updated: 2024/10/11 14:03:08 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* 
- gnl_strlen calculates the length of a string
*/

size_t	gnl_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

/* 
- gnl_strchr searches for a target character in an input string
- fn checks if 'str' is NULL or if 'target_char' is the null-terminator, then 
it iterates through 'str' and returns a pointer to the first occurrence of the
'target_char' if found or NULL if not found
- FOR GNL: used to locate the newline character ('\n') in the 'stash' buffer 
to determine if a complete line is available for extraction   
*/

char	*gnl_strchr(char *str, int target_char)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (target_char == '\0')
		return ((char *)&str[gnl_strlen(str)]);
	while (str[i] != '\0')
	{
		if (str[i] == (char) target_char)
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}

/* 
- gnl_strjoin concatenates two strings together, 'first str' and 'second str'
- fn checks if 'first_str' is NULL, and if so, initialises it as an empty string.
Memory is then dynamically allocated for 'joined_str' to store the concatenated 
result and then the characters are copied from 'first_str' and 'second_str' into
'joined str'. 'Joined_str' is then null-terminated, and the memory allocated for 
'first_str' is freed.
- FOR GNL: concatenates partial lines from the file with the 'stash' buffer
to build complete lines 
 */

char	*gnl_strjoin(char *first_str, char *second_str)
{
	size_t	first_index;
	size_t	second_index;
	char	*joined_str;

	if (!first_str)
	{
		first_str = (char *)malloc(1 * sizeof(char));
		first_str[0] = '\0';
	}
	if (first_str == NULL || second_str == NULL)
		return (NULL);
	joined_str = malloc(sizeof(char) * ((gnl_strlen(first_str)
					+ gnl_strlen(second_str)) + 1));
	if (joined_str == NULL)
		return (NULL);
	first_index = -1;
	second_index = 0;
	if (first_str)
		while (first_str[++first_index] != '\0')
			joined_str[first_index] = first_str[first_index];
	while (second_str[second_index] != '\0')
		joined_str[first_index++] = second_str[second_index++];
	joined_str[gnl_strlen(first_str) + gnl_strlen(second_str)] = '\0';
	free(first_str);
	return (joined_str);
}

/* 
- gnl_initialise_str initialises an empty string
- fn dynamically allocates memory for a single null-terminated character ('\0') 
and returns a pointer to it
- FOR GNL: initiliases an empty 'stash' buffer when the function is first called 
or when a line has been completely extracted
 */

char	*gnl_initialise_str(void)
{
	char	*string;

	string = (char *)malloc(sizeof(char) * 1);
	if (!string)
		return (NULL);
	*string = '\0';
	return (string);
}
