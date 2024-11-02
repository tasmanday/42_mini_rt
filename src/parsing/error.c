/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:07:45 by atang             #+#    #+#             */
/*   Updated: 2024/11/02 19:05:19 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	err_exit(t_Error error)
{
	printf(RED "\nError! ");
	if (error == 1)
		printf("Ambient light error\n\n");
	else if (error == 2)
		printf("Camera error\n\n");
	else if (error == 3)
		printf("Light error\n\n");
	printf("Exiting...\n\n" RST);
	exit(1);
}

void	warn_err_exit(const char *message, t_Error error)
{
	printf(RED"\n   Warning! %s\n"RST, message);
	printf(RED "\nError! ");
	if (error == 1)
		printf("Ambient light error\n\n");
	else if (error == 2)
		printf("Camera error\n\n");
	else if (error == 3)
		printf("Light error\n\n");
	printf("Exiting...\n\n" RST);
	exit(1);
}

int	err_free_exit(t_Error error, struct Object *current, t_Scene *scene)
{
	struct Object	*next;
	struct Object	*object;

	printf(RED "\nError! ");
	if (error == 3)
		printf("Sphere error\n\nExiting...\n\n"RST);
	else if (error == 4)
		printf("Plane error\n\nExiting...\n\n"RST);
	else if (error == 5)
		printf("Cylinder error\n\nExiting...\n\n"RST);
	if (scene && scene->mlx.mlx_ptr && scene->mlx.win_ptr)
		mlx_destroy_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr);
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
