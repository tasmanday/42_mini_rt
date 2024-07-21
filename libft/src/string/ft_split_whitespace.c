/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:29:10 by tday              #+#    #+#             */
/*   Updated: 2024/07/21 17:13:26 by tday             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
	Summary
	allocates memory and returns a substring from the input_str based on
	the delimiter character.

	Inputs
	input_str = The original string from which the substring is extracted.
	start_pos = A pointer to an integer that keeps track of the current position
	in the input_str.

	Outputs
	word = the substring extracted from the input string.
*/
static char	*allocate_word(const char *input_str, int *start_pos)
{
	char	*word;
	int		length;
	int		word_index;

	length = 0;
	while (input_str[*start_pos + length] != '\0' && \
	!ft_isspace(input_str[*start_pos + length]))
	{
		length++;
	}
	word = (char *) malloc((length + 1) * sizeof(char));
	if (!word)
		return (NULL);
	word_index = 0;
	while (input_str[*start_pos] != '\0' && !ft_isspace(input_str[*start_pos]))
	{
		word[word_index] = input_str[*start_pos];
		word_index++;
		(*start_pos)++;
	}
	word[word_index] = '\0';
	return (word);
}

/*
	Summary
	counts the number of words in a given string, separated by whitespace.

	Inputs
	input_str = The original string to count the words from.

	Outputs
	count = the number of words in the input string.
*/
static int	count_words(const char *input_str)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (input_str[i] != '\0')
	{
		while (ft_isspace(input_str[i]) && input_str[i] != '\0')
			i++;
		if (!ft_isspace(input_str[i]) && input_str[i] != '\0')
		{
			count++;
			while (!ft_isspace(input_str[i]) && input_str[i] != '\0')
				i++;
		}
	}
	return (count);
}

/*
	Summary
	frees the memory allocated for the array of substrings.

	Inputs
	result = A double pointer to the array of substrings.
	i = An integer representing the index of the last substring in the array.

	Outputs
	none.
*/
static void	free_allocated(char **result, int i)
{
	while (i >= 0)
	{
		free(result[i]);
		i--;
	}
	free(result);
}

/*
	Summary
	allocates memory and returns an array of substrings obtained by splitting
	the original string at whitespace characters.
	the array must end with a NULL pointer.

	Inputs
	input_str = original string.

	Outputs
	result = array of substrings.
*/
char	**ft_split_whitespace(const char *input_str)
{
	char	**result;
	int		i;
	int		current_word;
	int		word_count;

	i = 0;
	current_word = 0;
	word_count = count_words(input_str);
	result = (char **) malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (input_str[i] != '\0' && current_word < word_count)
	{
		while (ft_isspace(input_str[i]))
			i++;
		if (input_str[i] != '\0')
		{
			result[current_word] = allocate_word(input_str, &i);
			if (!result[current_word])
				return (free_allocated(result, current_word), NULL);
			current_word++;
		}
	}
	result[current_word] = NULL;
	return (result);
}
