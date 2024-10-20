/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:00:19 by atang             #+#    #+#             */
/*   Updated: 2024/10/19 10:12:02 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	is_normalized_vector(t_Vector3 *vector)
{
	return ((vector->x >= -1 && vector->x <= 1) && (vector->y >= -1
			&& vector->y <= 1) && (vector->z >= -1 && vector->z <= 1));
}

int	parse_sphere(char *line, t_Scene *scene)
{
	struct Object	*new_sphere;
	char			*token;

	(void)line;
	printf(G "Entering" RST " parse_sphere()\n\n");
	new_sphere = malloc(sizeof(struct Object));
	if (!new_sphere)
		return (0);
	new_sphere->type = SPHERE;
	new_sphere->next = NULL;
	token = strtok(NULL, " \t\n");
	if (!token || !parse_vector3(token, &new_sphere->u_data.sphere.centre))
		return (err_free_exit(new_sphere, 0));
	token = strtok(NULL, " \t\n");
	new_sphere->u_data.sphere.diameter = parse_float(&token);
	if (!token || !new_sphere->u_data.sphere.diameter)
		return (err_free_exit(new_sphere, 0));
	printf("   Parsed diameter: %f\n", new_sphere->u_data.sphere.diameter);
	token = strtok(NULL, " \t\n");
	if (!token || !parse_colour(token, &new_sphere->u_data.sphere.colour))
	{
		printf(RED "Exiting" RST " parse_sphere()\n");
		printf("---------------------------------------------------------\
			------\n");
		return (err_free_exit(new_sphere, 0));
	}
	if (!add_object(scene, new_sphere))
	{
		printf(RED "Error: Failed to add sphere to the scene.\n" RST);
		return (err_free_exit(new_sphere, 0));
	}
	printf(G "   SUCCESS - Sphere parsed and added!\n\n" RST);
	printf(RED "Exiting" RST " parse_sphere()\n\n");
	printf("---------------------------------------------------------------\n");
	return (1);
}

int	parse_plane(char *line, t_Scene *scene)
{
	struct Object	*new_plane;
	char			*token;

	(void)line;
	printf(G "Entering" RST " parse_plane()\n\n");
	new_plane = malloc(sizeof(struct Object));
	if (!new_plane)
	{
		printf(RED "Error: Memory allocation failed for plane object.\n" RST);
		return (0);
	}
	new_plane->type = PLANE;
	new_plane->next = NULL;
	token = strtok(NULL, " \t\n");
	if (!token || !parse_vector3(token, &new_plane->u_data.plane.point))
	{
		printf(RED "Error: Failed to parse point for plane.\n" RST);
		return (err_free_exit(new_plane, 0));
	}
	token = strtok(NULL, " \t\n");
	if (!token || !parse_vector3(token, &new_plane->u_data.plane.normal))
	{
		printf(RED "Error: Failed to parse normal for plane.\n" RST);
		return (err_free_exit(new_plane, 0));
	}
	if (!is_normalized_vector(&new_plane->u_data.plane.normal))
	{
		printf(RED "Error! Normal vector is not normalised \
			(range is -1 to 1).\n" RST);
		return (err_free_exit(new_plane, 0));
	}
	token = strtok(NULL, " \t\n");
	if (!token || !parse_colour(token, &new_plane->u_data.plane.colour))
	{
		printf(RED "Error: Failed to parse colour for plane.\n" RST);
		return (err_free_exit(new_plane, 0));
	}
	if (!add_object(scene, new_plane))
	{
		printf(RED "Error: Failed to add plane to the scene.\n" RST);
		return (err_free_exit(new_plane, 0));
	}
	printf(G "   SUCCESS - Plane parsed and added!\n\n" RST);
	printf(RED "Exiting" RST " parse_plane()\n\n");
	printf("---------------------------------------------------------------\n");
	return (1);
}

int	parse_cylinder(char *line, t_Scene *scene)
{
	struct Object	*new_cylinder;
	char			*token;

	(void)line;
	printf(G "Entering" RST " parse_cylinder()\n\n");
	new_cylinder = malloc(sizeof(struct Object));
	if (!new_cylinder)
		return (0);
	new_cylinder->type = CYLINDER;
	new_cylinder->next = NULL;
	token = strtok(NULL, " \t\n");
	if (!token || !parse_vector3(token, &new_cylinder->u_data.cylinder.centre))
		return (err_free_exit(new_cylinder, 0));
	token = strtok(NULL, " \t\n");
	if (!token || !parse_vector3(token, &new_cylinder->u_data.cylinder.axis))
		return (err_free_exit(new_cylinder, 0));
	token = strtok(NULL, " \t\n");
	new_cylinder->u_data.cylinder.diameter = parse_float(&token);
	if (!token || !new_cylinder->u_data.cylinder.diameter)
		return (err_free_exit(new_cylinder, 0));
	printf("   Parsed diameter: %f\n", new_cylinder->u_data.cylinder.diameter);
	token = strtok(NULL, " \t\n");
	new_cylinder->u_data.cylinder.height = parse_float(&token);
	if (!token || !new_cylinder->u_data.cylinder.height)
		return (err_free_exit(new_cylinder, 0));
	printf("   Parsed height: %f\n", new_cylinder->u_data.cylinder.height);
	token = strtok(NULL, " \t\n");
	if (!token || !parse_colour(token, &new_cylinder->u_data.cylinder.colour))
		return (err_free_exit(new_cylinder, 0));
	if (!add_object(scene, new_cylinder))
	{
		printf(RED "Error: Failed to add cylinder to the scene.\n" RST);
		return (err_free_exit(new_cylinder, 0));
	}
	printf(G "   SUCCESS - Cylinder parsed and added!\n\n" RST);
	printf(RED "Exiting" RST " parse_cylinder()\n\n");
	printf("---------------------------------------------------------------\n");
	return (1);
}
