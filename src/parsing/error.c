/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:07:45 by atang             #+#    #+#             */
/*   Updated: 2024/12/08 12:20:15 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	err_exit(t_Error error)
{
	if (error == 10)
		printf(RED" in AMBIENT LIGHT\n\n");
	else if (error == 11)
		printf(RED" in CAMERA\n\n");
	else if (error == 12)
		printf(RED" in LIGHT\n\n");
	printf("Exiting...\n\n" RST);
	exit(1);
}

void	warn_err_exit(const char *message, t_Error error)
{
	printf(RED"%s"RST, message);
	if (error == 10)
		printf(RED" in AMBIENT LIGHT\n\n");
	else if (error == 11)
		printf(RED" in CAMERA\n\n");
	else if (error == 12)
		printf(RED" in LIGHT\n\n");
	printf("Exiting...\n\n" RST);
	exit(1);
}

static void	print_error_message(t_Error error)
{
	if (error == 13)
		printf(RED" in SPHERE\n\n" RST);
	else if (error == 14)
		printf(RED" in PLANE\n\n" RST);
	else if (error == 15)
		printf(RED" in CYLINDER\n\n" RST);
}

static void	free_scene_objects(t_Scene *scene, struct Object *current)
{
	struct Object	*object;
	struct Object	*next;
	int				index;

	object = scene->objects;
	index = 0;
	while (object)
	{
		next = object->next;
		if (object == current)
		{
			object = next;
			index++;
			continue ;
		}
		printf("Freeing current object at index: %d\n", index);
		free(object);
		object = next;
		index++;
	}
	scene->objects = NULL;
	printf(G "All objects freed successfully.\n" RST);
}

int	err_free_exit(t_Error error, struct Object *current, t_Scene *scene)
{
	print_error_message(error);
	if (scene && scene->mlx.mlx_ptr && scene->mlx.win_ptr)
		mlx_destroy_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr);
	if (scene && scene->objects)
		free_scene_objects(scene, current);
	printf(RED"\nExiting...\n\n" RST);
	exit(1);
}
