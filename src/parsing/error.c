/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:07:45 by atang             #+#    #+#             */
/*   Updated: 2024/11/03 18:53:29 by atang            ###   ########.fr       */
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

int	err_free_exit(t_Error error, struct Object *current, t_Scene *scene)
{
	struct Object	*next;
	struct Object	*object;
	int 			index;

	index = 0;
	if (error == 13)
		printf(RED" in SPHERE\n\n\n"RST);
	else if (error == 14)
		printf(RED" in PLANE\n\n"RST);
	else if (error == 15)
		printf(RED" in CYLINDER\n\n"RST);
	if (scene && scene->mlx.mlx_ptr && scene->mlx.win_ptr)
		mlx_destroy_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr);
	if (current)
	{
		printf("Freeing current object at index: %d at address: %p\n", index, (void *)current);
		free(current);
		current = NULL;
	}
	if (scene && scene->objects)
	{
		object = scene->objects;
		while (object)
		{
			next = object->next;
			printf("Freeing current object at index: %d at address: %p\n", index, (void *)current);
			free(object);
			object = next;
			index++;
		}
		scene->objects = NULL;
	}
	free(scene);
	printf(RED"\nExiting...\n\n"RST);
	exit(1);
}

int	warn_err_free_exit(const char *message, t_Error error, struct Object *current, t_Scene *scene)
{
	struct Object	*next;
	struct Object	*object;
	int 			index;

	(void)current;
	index = 0;
	printf(RED "\n   Error! %s", message);
	if (error == 13)
		printf("in SPHERE\n\nExiting...\n\n"RST);
	else if (error == 14)
		printf("in PLANE\n\nExiting...\n\n"RST);
	else if (error == 15)
		printf("in CYLINDER\n\nExiting...\n\n"RST);
	if (scene && scene->mlx.mlx_ptr && scene->mlx.win_ptr)
		mlx_destroy_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr);
	/*	
	if (current)
	{
		printf("Freeing current object at index: %d at address: %p\n", index, (void *)current);
		free(current);
		//current = NULL;
	}
	if (scene && scene->objects)
	{
		object = scene->objects;
		while (object)
		{
			next = object->next;
			printf("Freeing current object at index: %d at address: %p\n", index, (void *)current);
			free(object);
			object = next;
			index++;
		}
		scene->objects = NULL;
	}
	*/
    if (scene && scene->objects)
    {
        object = scene->objects;
        while (scene->object_count > 0 && object)
        {
            next = object->next;
            printf("Freeing object at address: %p\n", (void *)object);
            free(object);
            object = next;
            scene->object_count--; // Decrement object count
        }
        scene->objects = NULL; // Clear the head pointer
        printf(G "All objects freed successfully.\n" RST);
    }
	free(scene);
	exit(1);
}

int	err_return(const char *message)
{
	printf(RED "   Error! %s\n\n" RST, message);
	return (FAILURE);
}
