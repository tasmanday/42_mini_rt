/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 22:48:28 by atang             #+#    #+#             */
/*   Updated: 2025/01/07 22:48:31 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_sphere(const struct Object *object)
{
	if (object->type != SPHERE)
		return ;
	printf("      Center: %f, %f, %f\n",
		object->u_data.sphere.center.x,
		object->u_data.sphere.center.y,
		object->u_data.sphere.center.z);
	printf("      Diameter: %f\n", object->u_data.sphere.diameter);
	printf("      Colour: %f, %f, %f",
		object->u_data.sphere.colour.r,
		object->u_data.sphere.colour.g,
		object->u_data.sphere.colour.b);
}

void	print_plane(const struct Object *object)
{
	if (object->type != PLANE)
		return ;
	printf("      Point: %f, %f, %f\n",
		object->u_data.plane.point.x,
		object->u_data.plane.point.y,
		object->u_data.plane.point.z);
	printf("      Normal: %f, %f, %f\n",
		object->u_data.plane.normal.x,
		object->u_data.plane.normal.y,
		object->u_data.plane.normal.z);
	printf("      Colour: %f, %f, %f",
		object->u_data.plane.colour.r,
		object->u_data.plane.colour.g,
		object->u_data.plane.colour.b);
}

void	print_cylinder(const struct Object *object)
{
	if (object->type != CYLINDER)
		return ;
	printf("      Center: %f, %f, %f\n",
		object->u_data.cylinder.center.x,
		object->u_data.cylinder.center.y,
		object->u_data.cylinder.center.z);
	printf("      Axis: %f, %f, %f\n",
		object->u_data.cylinder.axis.x,
		object->u_data.cylinder.axis.y,
		object->u_data.cylinder.axis.z);
	printf("      Diameter: %f\n", object->u_data.cylinder.diameter);
	printf("      Height: %f\n", object->u_data.cylinder.height);
	printf("      Colour: %f, %f, %f",
		object->u_data.cylinder.colour.r,
		object->u_data.cylinder.colour.g,
		object->u_data.cylinder.colour.b);
}
/*
void	print_all_objects(const t_Scene *scene)
{
	struct Object	*current;
	int				position;

	current = scene->objects;
	printf(G "\nEntering" RST " print_all_objects()\n\n");
	printf("   NUMBER OF OBJECTS IN SCENE: %d\n", scene->object_count);
	if (!current)
		printf("\n   No objects in the scene!");
	position = 1;
	while (current)
	{
		printf("\n-> " U "OBJECT LIST POSITION: %d\n\n" RST, position);
		printf("      Printing object of type: ");
		if (current->type == SPHERE)
		{
			printf(Y "SPHERE\n" RST);
			print_sphere(current);
		}
		else if (current->type == PLANE)
		{
			printf(B "PLANE\n" RST);
			print_plane(current);
		}
		else if (current->type == CYLINDER)
		{
			printf(C "CYLINDER\n" RST);
			print_cylinder(current);
		}
		else
			printf("Unknown object type\n");
		current = current->next;
		position++;
	}
	printf(RED "\n\nExiting" RST " print_all_objects()\n");
}
*/

static void	print_object_details(const struct Object *object, int position)
{
	printf("\n-> " U "OBJECT LIST POSITION: %d\n\n" RST, position);
	printf("      Printing object of type: ");
	if (object->type == SPHERE)
	{
		printf(Y "SPHERE\n" RST);
		print_sphere(object);
	}
	else if (object->type == PLANE)
	{
		printf(B "PLANE\n" RST);
		print_plane(object);
	}
	else if (object->type == CYLINDER)
	{
		printf(C "CYLINDER\n" RST);
		print_cylinder(object);
	}
	else
	{
		printf("Unknown object type\n");
	}
}

void	print_all_objects(const t_Scene *scene)
{
	struct Object	*current;
	int				position;

	current = scene->objects;
	printf(G "\nEntering" RST " print_all_objects()\n\n");
	printf("   NUMBER OF OBJECTS IN SCENE: %d\n", scene->object_count);
	if (!current)
		printf("\n   No objects in the scene!");
	position = 1;
	while (current)
	{
		print_object_details(current, position);
		current = current->next;
		position++;
	}
	printf(RED "\n\nExiting" RST " print_all_objects()\n");
}
