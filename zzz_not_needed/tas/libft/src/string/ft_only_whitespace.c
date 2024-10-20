/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_only_whitespace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:23:32 by tday              #+#    #+#             */
/*   Updated: 2024/07/21 16:29:27 by tday             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
	Summary
	Checks if a string contains only whitespace characters.

	Inputs
	[char *] input: Pointer to the input string to be checked.

	Outputs
	[bool] Returns true if the string contains only whitespace characters,
	otherwise returns false.
*/
bool	ft_only_whitespace(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (false);
		i++;
	}
	return (true);
}
