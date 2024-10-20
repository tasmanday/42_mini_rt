/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:07:45 by atang             #+#    #+#             */
/*   Updated: 2024/10/20 13:50:44 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	err_exit(t_Error error)
{
	printf(RED "\nError! ");
	if (error == 0)
		printf("Invalid float value\n\n");
	else if (error == 1)
		printf("Invalid integer value\n\n");
	else if (error == 2)
		printf("Invalid vector\n\n");
	else if (error == 3)
		printf("Missing input value(s)\n\n");
	else if (error == 4)
		printf("Colour value outside of range (0 to 255)\n\n");
	else if (error == 5)
		printf("Ambient light ratio outside of range (0.0 to 1.0)\n\n");
	else if (error == 6)
		printf("Light brightness ratio outside of range (0.0 to 1.0)\n\n");
	else if (error == 7)
		printf("Camera FOV outside of range (0 to 180)\n\n");
	printf("Exiting...\n\n" RST);
	exit(1);
}

int	err_free_exit(struct Object *current, t_Scene *scene)
{
	struct Object	*next;
	struct Object	*object;

	if (scene && scene->mlx.mlx_ptr && scene->mlx.win_ptr)
	{
		mlx_destroy_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr);
	}
	if (current)
	{
		printf("Freeing current object at address: %p\n", (void *)current);
		free(current);
		current = NULL;
	}
	if (scene && scene->objects)
	{
		object = scene->objects;
		while (object)
		{
			next = object->next;
			free(object);
			object = next;
		}
		scene->objects = NULL;
	}
	free(scene);
	exit(1);
}

int	err_return(const char *message)
	{
	printf(RED "\nError! %s\n\n" RST, message);
	return (FAILURE);
}
