/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_scrap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:07:45 by atang             #+#    #+#             */
/*   Updated: 2024/12/08 12:07:45 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
// KEEP
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
		printf("Missing or extra input value(s)\n\n");
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
*/

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


/*
--> OG err_free_exit	
int	err_free_exit(t_Error error, struct Object *current, t_Scene *scene)
{
	struct Object	*next;
	struct Object	*object;
	int				index;

	index = 0;
	if (error == 13)
		printf(RED" in SPHERE\n\n"RST);
	else if (error == 14)
		printf(RED" in PLANE\n\n"RST);
	else if (error == 15)
		printf(RED" in CYLINDER\n\n"RST);
	if (scene && scene->mlx.mlx_ptr && scene->mlx.win_ptr)
		mlx_destroy_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr);
	if (scene && scene->objects)
	{
		object = scene->objects;
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
	printf(RED"\nExiting...\n\n"RST);
	exit(1);
}
*/

/*
--> OG warn_err_free_exit
int	warn_err_free_exit(const char *message, t_Error error,
	struct Object *current, t_Scene *scene)
{
	struct Object	*next;
	struct Object	*object;
	int				index;

	(void) current;
	index = 0;
	printf(RED "\n   Error! %s", message);
	if (error == 13)
		printf(" in SPHERE\n\nExiting...\n\n"RST);
	else if (error == 14)
		printf(" in PLANE\n\nExiting...\n\n"RST);
	else if (error == 15)
		printf(" in CYLINDER\n\nExiting...\n\n"RST);
	if (scene && scene->objects)
	{
		object = scene->objects;
		while (object)
		{
			next = object->next;
			printf("Freeing current object at index: %d\n", index);
			free(object);
			object = next;
			index++;
		}
		scene->objects = NULL;
		printf(G "All objects freed successfully.\n" RST);
	}
	if (scene && scene->objects)
	{
		object = scene->objects;
		while (scene->object_count > 0 && object)
		{
			next = object->next;
			printf("Freeing object at address: %p\n", (void *)object);
			free(object);
			object = next;
			scene->object_count--;
		}
		scene->objects = NULL;
		printf(G "All objects freed successfully!\n" RST);
	}
	exit(1);
}
*/

