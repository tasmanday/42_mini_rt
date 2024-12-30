/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:44:56 by atang             #+#    #+#             */
/*   Updated: 2024/10/19 10:07:13 by sentry           ###   ########.fr       */
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

int	add_object(t_Scene *scene, struct Object *new_object)
{
	struct Object	*current;

	printf(G "   Entering" RST " add_object()\n");
	if (!scene)
	{
		printf("      Error: Scene is NULL.\n");
		return (0);
	}
	if (!new_object)
	{
		printf("      Error: New object is NULL.\n");
		return (0);
	}
	if (!scene->objects)
	{
		scene->objects = new_object;
		printf("      First object added to the scene!\n");
	}
	else
	{
		current = scene->objects;
		while (current->next)
		{
			current = current->next;
		}
		current->next = new_object;
	}
	scene->object_count++;
	printf(G "      Object added! New count: %d\n" RST, scene->object_count);
	print_objects_in_scene(scene->objects);
	printf(RED "   Exiting" RST " add_object()\n");
	return (1);
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
