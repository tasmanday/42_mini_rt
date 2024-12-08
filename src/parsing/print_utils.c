/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:07:45 by atang             #+#    #+#             */
/*   Updated: 2024/12/08 11:51:27 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int print_error_and_return(const char *message, const char *token)
{
    if (token)
        printf(RED "\n   %s: '%s'" RST, message, token);
    else
        printf(RED "\n   %s" RST, message);
    return (FAILURE);
}

void	print_objects_in_scene(struct Object *objects)
{
	struct Object	*temp;
	const char		*type_str;

	temp = objects;
	printf("      Current objects in scene:\n");
	while (temp)
	{
		type_str = get_object_type_str(temp->type);
		printf("      Object type: %s\n", type_str);
		temp = temp->next;
	}
}