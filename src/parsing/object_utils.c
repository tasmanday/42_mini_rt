/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:44:56 by atang             #+#    #+#             */
/*   Updated: 2024/12/08 11:51:25 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

const char	*get_object_type_str(int type)
{
	if (type == SPHERE)
		return ("SPHERE");
	else if (type == PLANE)
		return ("PLANE");
	else if (type == CYLINDER)
		return ("CYLINDER");
	else
		return ("Unknown");
}

static int	handle_null_object_error(const char *message)
{
	printf("      Error: %s\n", message);
	return (FAILURE);
}

static void	append_object_to_scene(t_Scene *scene, struct Object *new_object)
{
	struct Object	*current;

	current = scene->objects;
	while (current->next)
	{
		current = current->next;
	}
	current->next = new_object;
}

int	add_object(t_Scene *scene, struct Object *new_object)
{
	printf(G "   Entering" RST " add_object()\n\n");
	if (!scene)
		return (handle_null_object_error("Error: Scene is NULL."));
	if (!new_object)
		return (handle_null_object_error("Error: New object is NULL."));
	new_object->next = NULL;
	if (!scene->objects)
	{
		scene->objects = new_object;
		printf("      First object added to the scene!\n");
	}
	else
	{
		append_object_to_scene(scene, new_object);
	}
	scene->object_count++;
	printf(G "      Object added! New count: %d\n" RST, scene->object_count);
	print_objects_in_scene(scene->objects);
	printf(RED "\n   Exiting" RST " add_object()\n\n");
	return (SUCCESS);
}

void	free_objects(t_Scene *scene)
{
	struct Object	*current;
	struct Object	*next;

	current = scene->objects;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	scene->objects = NULL;
	scene->object_count = 0;
}
