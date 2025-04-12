/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 22:52:18 by atang             #+#    #+#             */
/*   Updated: 2025/02/02 22:29:29 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_dimensions(char **line, float *diameter, float *height)
{
	char	*token;

	if (get_next_token(line, &token) == FAILURE)
		return (FAILURE);
	*diameter = parse_float(&token);
	if (*diameter <= 0.0f)
		return (FAILURE);
	if (height)
	{
		if (get_next_token(line, &token) == FAILURE)
			return (FAILURE);
		*height = parse_float(&token);
		if (*height <= 0.0f)
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	init_object(struct Object **obj, int type)
{
	*obj = malloc(sizeof(struct Object));
	if (!*obj)
		return (FAILURE);
	(*obj)->type = type;
	(*obj)->next = NULL;
	return (SUCCESS);
}

int	parse_sphere(char **line, t_Scene *scene)
{
	struct Object	*new_sphere;
	float			diameter;
	char			*token;

	diameter = 0.0f;
	if (init_object(&new_sphere, SPHERE) == FAILURE)
		return (FAILURE);
	if (parse_vector3(line, &new_sphere->u_data.sphere.center) == FAILURE)
		warn_err_free_exit("Failed sphere center", 13, new_sphere, scene);
	if (parse_dimensions(line, &diameter, NULL) == FAILURE)
		warn_err_free_exit("Invalid diameter", 13, new_sphere, scene);
	new_sphere->u_data.sphere.diameter = diameter;
	if (parse_rgb(&new_sphere->u_data.sphere.colour, line) == FAILURE)
		err_free_exit(13, new_sphere, scene);
	if (get_next_token(line, &token) == SUCCESS)
		warn_err_free_exit("Excess sphere value(s)", 13, new_sphere, scene);
	if (add_object(scene, new_sphere) != SUCCESS)
		warn_err_free_exit("Could not add object", 13, new_sphere, scene);
	return (SUCCESS);
}

int	parse_cylinder(char **line, t_Scene *scene)
{
	struct Object	*new_cylinder;
	float			diameter;
	float			height;
	char			*token;

	diameter = 0.0f;
	height = 0.0f;
	if (init_object(&new_cylinder, CYLINDER) == FAILURE)
		return (FAILURE);
	if (parse_vector3(line, &new_cylinder->u_data.cylinder.center) == FAILURE)
		warn_err_free_exit("Failed cylinder center", 15, new_cylinder, scene);
	if (parse_vector3(line, &new_cylinder->u_data.cylinder.axis) == FAILURE)
		warn_err_free_exit("Failed cylinder axis", 15, new_cylinder, scene);
	if (!is_normalized_vector(&new_cylinder->u_data.cylinder.axis))
		warn_err_free_exit("Vector not normalized", 15, new_cylinder, scene);
	if (parse_dimensions(line, &diameter, &height) == FAILURE)
		warn_err_free_exit("Invalid dimensions", 15, new_cylinder, scene);
	new_cylinder->u_data.cylinder.diameter = diameter;
	new_cylinder->u_data.cylinder.height = height;
	if (parse_rgb(&new_cylinder->u_data.cylinder.colour, line) == FAILURE)
		err_free_exit(15, new_cylinder, scene);
	if (get_next_token(line, &token) == SUCCESS)
		warn_err_free_exit("Excess values", 15, new_cylinder, scene);
	return (add_object(scene, new_cylinder));
}

int	parse_plane(char **line, t_Scene *scene)
{
	struct Object	*new_plane;
	char			*token;

	printf(G "Entering" RST " parse_plane()\n\n");
	new_plane = malloc(sizeof(struct Object));
	if (!new_plane)
		return (FAILURE);
	new_plane->type = PLANE;
	new_plane->next = NULL;
	if (parse_vector3(line, &new_plane->u_data.plane.point) == FAILURE)
		warn_err_free_exit("Failed to parse point", 14, new_plane, scene);
	if (parse_vector3(line, &new_plane->u_data.plane.normal) == FAILURE)
		warn_err_free_exit("Failed to parse normal", 14, new_plane, scene);
	if (!is_normalized_vector(&new_plane->u_data.plane.normal))
		warn_err_free_exit("Vector is not normalised (-1 to 1)", 14,
			new_plane, scene);
	if (parse_rgb(&new_plane->u_data.plane.colour, line) == FAILURE)
		err_free_exit(14, new_plane, scene);
	if (get_next_token(line, &token) == SUCCESS)
		warn_err_free_exit("Excess plane value(s)", 14, new_plane, scene);
	if (add_object(scene, new_plane) != SUCCESS)
		warn_err_free_exit("Could not add object", 14, new_plane, scene);
	printf(G "   SUCCESS - Plane parsed and added!\n\n" RST);
	printf(RED "Exiting" RST " parse_plane()\n\n");
	return (SUCCESS);
}
