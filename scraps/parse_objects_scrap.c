/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_scrap.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:00:19 by atang             #+#    #+#             */
/*   Updated: 2024/12/07 13:22:27 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
static int	is_normalized_vector(t_Vector3 *vector)
{
	return ((vector->x >= -1 && vector->x <= 1) && (vector->y >= -1
			&& vector->y <= 1) && (vector->z >= -1 && vector->z <= 1));
}
*/

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
	if (!token || !parse_vector3(&new_sphere->u_data.sphere.centre))
		return (err_free_exit(new_sphere, 0));
	token = strtok(NULL, " \t\n");
	new_sphere->u_data.sphere.diameter = parse_float(&token);
	if (!token || !new_sphere->u_data.sphere.diameter)
		return (err_free_exit(new_sphere, 0));
	printf("   Parsed diameter: %f\n", new_sphere->u_data.sphere.diameter);
	token = strtok(NULL, " \t\n");
	if (!token || !parse_rgb(&new_sphere->u_data.sphere.colour, &token))
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
	return(SUCCESS); // changed from return (1)
}

/*
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
	return(SUCCESS); // changed from return (1)
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
	return(SUCCESS); // changed from return (1)
}
*/

/*
// OG parse_sphere	
int	parse_sphere(t_Scene *scene)
{
	struct Object	*new_sphere;
	char			*token;
	float			diameter;

	printf(G "Entering" RST " parse_sphere()\n\n");
	new_sphere = malloc(sizeof(struct Object));
	if (!new_sphere)
		return (FAILURE);
	new_sphere->type = SPHERE;
	new_sphere->next = NULL;
	if (parse_vector3(&new_sphere->u_data.sphere.centre) == FAILURE)
		warn_err_free_exit("Failed sphere centre", 13, new_sphere, scene);
	if (get_next_token(&token) == FAILURE)
		warn_err_free_exit("No input for diameter", 13, new_sphere, scene);
	diameter = parse_float(&token);
	if (diameter == FAILURE)
		err_free_exit(13, new_sphere, 0);
	new_sphere->u_data.sphere.diameter = diameter;
	if (new_sphere->u_data.sphere.diameter <= 0.0f)
		warn_err_free_exit("Invalid diameter", 13, new_sphere, scene);
	printf("\n   -> Parsed diameter: %f\n\n",
		new_sphere->u_data.sphere.diameter);
	if (parse_rgb(&new_sphere->u_data.sphere.colour, &token) == FAILURE)
		err_free_exit(13, new_sphere, scene);
	if (get_next_token(&token) == SUCCESS)
		warn_err_free_exit("Excess sphere value(s)", 13, new_sphere, scene);
	if (!add_object(scene, new_sphere))
		warn_err_free_exit("Could not add object", 13, new_sphere, scene);
	printf(G "   SUCCESS - Sphere parsed and added!\n\n" RST);
	printf(RED "Exiting" RST " parse_sphere()\n\n");
	printf("---------------------------------------------------------------\n");
	return (SUCCESS);
}

// OG parse_plane
int	parse_plane(char *line, t_Scene *scene)
{
	struct Object	*new_plane;
	char			*token;

	(void)line;
	printf(G "Entering" RST " parse_plane()\n\n");
	new_plane = malloc(sizeof(struct Object));
	if (!new_plane)
		return (FAILURE);
	new_plane->type = PLANE;
	new_plane->next = NULL;
	if (parse_vector3(&new_plane->u_data.plane.point) == FAILURE)
		warn_err_free_exit("Failed to parse point", 14, new_plane, scene);
	if (parse_vector3(&new_plane->u_data.plane.normal) == FAILURE)
		warn_err_free_exit("Failed to parse normal", 14, new_plane, scene);
	if (!is_normalized_vector(&new_plane->u_data.plane.normal))
		warn_err_free_exit("Vector is not normalised (-1 to 1)", 14, new_plane, scene);
	if (parse_rgb(&new_plane->u_data.plane.colour, &token) == FAILURE)
		err_free_exit(14, new_plane, scene);
	if (get_next_token(&token) == SUCCESS)
		warn_err_free_exit("Excess plane value(s)", 14, new_plane, scene);
	if (!add_object(scene, new_plane))
		warn_err_free_exit("Could not add object", 14, new_plane, scene);
	printf(G "   SUCCESS - Plane parsed and added!\n\n" RST);
	printf(RED "Exiting" RST " parse_plane()\n\n");
	printf("---------------------------------------------------------------\n");
	return(SUCCESS); // changed from return (1)
}

// OG parse_cylinder
int	parse_cylinder(char *line, t_Scene *scene)
{
	struct Object	*new_cylinder;
	char			*token;
	float			diameter;
	float			height;

	(void)line;
	printf(G "Entering" RST " parse_cylinder()\n\n");
	new_cylinder = malloc(sizeof(struct Object));
	if (!new_cylinder)
		return (FAILURE);
	new_cylinder->type = CYLINDER;
	new_cylinder->next = NULL;
	if (parse_vector3(&new_cylinder->u_data.cylinder.centre) == FAILURE)
		warn_err_free_exit("Failed cylinder centre", 15, new_cylinder, scene);
	if (parse_vector3(&new_cylinder->u_data.cylinder.axis) == FAILURE)
		warn_err_free_exit("Failed cylinder axis", 15, new_cylinder, scene);
	if (!is_normalized_vector(&new_cylinder->u_data.cylinder.axis))
		warn_err_free_exit("Vector is not normalised (-1 to 1)", 15, new_cylinder, scene);
	if (get_next_token(&token) == FAILURE)
		warn_err_free_exit("No input for diameter", 13, new_cylinder, scene);
	diameter = parse_float(&token);
	if (diameter == FAILURE)
		err_free_exit(15, new_cylinder, 0);
	new_cylinder->u_data.cylinder.diameter = diameter;
	if (new_cylinder->u_data.cylinder.diameter <= 0.0f)
		warn_err_free_exit("Invalid diameter", 15, new_cylinder, scene);
	printf("\n   -> Parsed diameter: %f\n\n", new_cylinder->u_data.cylinder.diameter);
	if (get_next_token(&token) == FAILURE)
		warn_err_free_exit("No input for height", 13, new_cylinder, scene);
	height = parse_float(&token);
	if (height == FAILURE)
		err_free_exit(15, new_cylinder, 0);
	new_cylinder->u_data.cylinder.height = height;
	if (new_cylinder->u_data.cylinder.height <= 0.0f)
		warn_err_free_exit("Invalid height", 15, new_cylinder, scene);
	printf("\n   -> Parsed height: %f\n\n", new_cylinder->u_data.cylinder.height);
	if (parse_rgb(&new_cylinder->u_data.cylinder.colour, &token) == FAILURE)
		err_free_exit(15, new_cylinder, scene);
	if (get_next_token(&token) == SUCCESS)
		warn_err_free_exit("Excess cylinder value(s)", 15, new_cylinder, scene);
	if (!add_object(scene, new_cylinder))
		warn_err_free_exit("Could not add object", 15, new_cylinder, scene);
	printf(G "   SUCCESS - Cylinder parsed and added!\n\n" RST);
	printf(RED "Exiting" RST " parse_cylinder()\n\n");
	printf("---------------------------------------------------------------\n");
	return (SUCCESS);
}
*/
