/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:07:45 by atang             #+#    #+#             */
/*   Updated: 2025/02/02 19:35:24 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	print_error_and_return(const char *message, const char *token)
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

void	print_scene_info(t_Scene *scene)
{
	printf(M "---> PRINTING ELEMENTS AND OBJECTS <---\n\n" RST);
	printf(G "Entering" RST " print_ambient_light(), print_camera(), and \
print_light()\n");
	print_ambient_light(&scene->ambient_light);
	print_camera(&scene->camera);
	print_light(&scene->light);
	printf(RED "\nExiting" RST " print_ambient_light(), print_camera(), \
and print_light()\n\n");
	printf("---------------------------------------------------------------\n");
	print_all_objects(scene);
}
