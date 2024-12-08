/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:07:45 by atang             #+#    #+#             */
/*   Updated: 2024/12/08 12:19:53 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	err_return(const char *message)
{
	printf(RED "\nError! %s\n\n" RST, message);
	return (FAILURE);
}

static void	print_warning_message(const char *message, t_Error error)
{
	printf(RED "\n   Error! %s", message);
	if (error == 13)
		printf(" in SPHERE\n\nExiting...\n\n" RST);
	else if (error == 14)
		printf(" in PLANE\n\nExiting...\n\n" RST);
	else if (error == 15)
		printf(" in CYLINDER\n\nExiting...\n\n" RST);
}

static void	free_scene_objects_and_count(t_Scene *scene)
{
	struct Object	*object;
	struct Object	*next;
	int				index;

	object = scene->objects;
	index = 0;
	while (object)
	{
		next = object->next;
		printf("Freeing object at index: %d\n", index);
		free(object);
		object = next;
		index++;
	}
	scene->objects = NULL;
	printf(G "All objects freed successfully.\n" RST);
}

int	warn_err_free_exit(const char *message, t_Error error,
	struct Object *current, t_Scene *scene)
{
	(void) current;
	print_warning_message(message, error);
	if (scene && scene->objects)
		free_scene_objects_and_count(scene);
	exit(1);
}
