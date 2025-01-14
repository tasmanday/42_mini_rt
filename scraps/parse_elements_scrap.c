/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_scrap.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:59:55 by atang             #+#    #+#             */
/*   Updated: 2024/12/07 22:19:39 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
int	parse_ambient_light(char *line, t_AmbientLight *ambient_light)
{
	char	*token;
	float	ratio;

	(void) line;
	printf(G "Entering" RST " parse_ambient_light()\n");
	//if (!get_next_token(&token))
	if (get_next_token(&token) == FAILURE)
		err_exit(3);
	ratio = parse_float(&token);
	if (ratio == FAILURE)
		err_exit(0);
	ambient_light->ratio = ratio;
	if (ambient_light->ratio < 0.0f || ambient_light->ratio > 1.0f)
		err_exit(5);
	printf("\n   Parsed ratio: %f\n", ambient_light->ratio);
	//if (!get_next_token(&token))
	if (get_next_token(&token) == FAILURE)
		err_exit(3);
	//parse_colour(token, &ambient_light->colour);
	if (parse_colour(token, &ambient_light->colour) == 3)
		err_exit(3);
	//if (get_next_token(&token) == SUCCESS)
		//err_exit(3);
	printf(G "   SUCCESS - Ambient Light parsed and added!\n\n");
	printf(RED "Exiting" RST " parse_ambient_light()\n\n");
	printf("---------------------------------------------------------------\n");
	return (SUCCESS);
}
*/

/*
int	parse_ambient_light(char *line, t_AmbientLight *ambient_light)
{
	char	*token;
	float	ratio;

	(void) line;
	printf(G "Entering" RST " parse_ambient_light()\n");
	//if (!get_next_token(&token))
	if (get_next_token(&token) == FAILURE)
		err_exit(1);
	ratio = parse_float(&token);
	if (ratio == FAILURE)
		err_exit(1);
	ambient_light->ratio = ratio;
	//if (ambient_light->ratio < 0.0f || ambient_light->ratio > 1.0)
	if (ambient_light->ratio < 0.0f || ambient_light->ratio > 1.0f)
	{
		printf(RED"\n   Warning! Ambient light ratio out of range (0.0 to 1.0)\n"RST);
		err_exit(1);
	}
	printf("\n   Parsed ratio: %f\n", ambient_light->ratio);
	//if (!get_next_token(&token))
	if (get_next_token(&token) == FAILURE)
		err_exit(1);
	//parse_colour(token, &ambient_light->colour);
	if (parse_colour(token, &ambient_light->colour) == FAILURE)
		err_exit(1);
	if (get_next_token(&token) == SUCCESS)
	{
		printf(RED"\n   Warning! Excess ambient light values\n"RST);
		err_exit(1);
	}
	printf(G "   SUCCESS - Ambient Light parsed and added!\n\n");
	printf(RED "Exiting" RST " parse_ambient_light()\n\n");
	printf("---------------------------------------------------------------\n");
	return (SUCCESS);
}
*/

/*
// THIS ONE
int	parse_ambient_light(char *line, t_AmbientLight *ambient_light)
{
	char	*token;
	float	ratio;

	(void) line;
	printf(G "Entering" RST " parse_ambient_light()\n");
	if (get_next_token(&token) == FAILURE)
	//  if (get_next_token(&token, &line) == FAILURE)
		warn_err_exit("No token found", 1);
	ratio = parse_float(&token);
	if (ratio == FAILURE)
		err_exit(1);
	ambient_light->ratio = ratio;
	if (ambient_light->ratio < 0.0f || ambient_light->ratio > 1.0f)
		warn_err_exit("Ambient light ratio out of range (0.0 to 1.0)", 1);
	printf("\n   Parsed ratio: %f\n", ambient_light->ratio);
	if (get_next_token(&token) == FAILURE)
	//  if (get_next_token(&token, &line) == FAILURE)
		warn_err_exit("No token found", 1);
	if (parse_colour(token, &ambient_light->colour) == FAILURE)
		err_exit(1);
	if (get_next_token(&token) == SUCCESS)
	//if (get_next_token(&token, &line) == SUCCESS)
		warn_err_exit("Excess ambient light values", 1);
	printf(G "   SUCCESS - Ambient Light parsed and added!\n\n");
	printf(RED "Exiting" RST " parse_ambient_light()\n\n");
	printf("---------------------------------------------------------------\n");
	return (SUCCESS);
}
*/
int parse_ambient_light(char *line, t_AmbientLight *ambient_light)
{
    char *token;
    float ratio;
    //int i = 0; // Counter for RGB values
	(void)line;

    printf(G "Entering" RST " parse_ambient_light()\n\n");
    if (get_next_token(&token) == FAILURE)
        warn_err_exit("No token found", 1);
    ratio = parse_float(&token);
    if (ratio == FAILURE)
        err_exit(1);
    ambient_light->ratio = ratio;
    if (ambient_light->ratio < 0.0f || ambient_light->ratio > 1.0f)
        warn_err_exit("Ambient light ratio out of range (0.0 to 1.0)", 1);
    printf("   -> Parsed ratio: %f\n", ambient_light->ratio);
    // Get the color token (RGB values)
    /*
    while (i < 3) // Expecting exactly 3 tokens for RGB
    {
        if (get_next_token(&token) == FAILURE)
            warn_err_exit("No more tokens found for RGB values", 1);

        int value = atoi(token); // Assuming parse_colour can handle int values.
        if (i == 0)
            ambient_light->colour.r = value;
        else if (i == 1)
            ambient_light->colour.g = value;
        else if (i == 2)
            ambient_light->colour.b = value;
        i++; // Increment the counter for each RGB value parsed
    }
    */
    if (parse_rgb(&ambient_light->colour, &token) != SUCCESS)
    {
        return (FAILURE); // Handle any parsing errors
    }
    printf("   -> Parsed colour: R = %d, G = %d, B = %d\n", ambient_light->colour.r,
		ambient_light->colour.g, ambient_light->colour.b);
    if (get_next_token(&token) == SUCCESS)
        warn_err_exit("Excess ambient light values", 1);
    printf(G "   SUCCESS - Ambient Light parsed and added!\n\n");
    printf(RED "Exiting" RST " parse_ambient_light()\n\n");
    printf("---------------------------------------------------------------\n");
    return (SUCCESS);
}

/*
int parse_ambient_light(char *line, t_AmbientLight *ambient_light)
{
    char *token = line;
    float ratio;

    printf(G "Entering" RST " parse_ambient_light()\n");
    if (get_next_token(&token) == FAILURE)
        warn_err_exit("No token found", 1);
    
    ratio = strtof(token, NULL);
    if (ratio == FAILURE)
        err_exit(1);
    if (ratio < 0.0f || ratio > 1.0f)
        warn_err_exit("Ambient light ratio out of range (0.0 to 1.0)", 1); 
    ambient_light->ratio = ratio; 
    printf("\n   Parsed ratio: %f\n", ambient_light->ratio);
    if (get_next_token(&token) == FAILURE)
        warn_err_exit("No token found", 1);
    if (parse_colour(token, &ambient_light->colour) == FAILURE)
        err_exit(1);
    printf(G "   SUCCESS - Ambient Light parsed and added!\n\n");
    printf(RED "Exiting" RST " parse_ambient_light()\n\n");
    printf("---------------------------------------------------------------\n");
    return (SUCCESS);
}
*/

/*
int parse_ambient_light(char *line, t_AmbientLight *ambient_light)
{
    char *token;
    int values[3];
    int i = 0;

    // Step 1: Parse the ratio as the first token (float)
    token = strtok(line, " ");
    if (!token)
        return (FAILURE);
    ambient_light->ratio = strtof(token, NULL);

    // Step 2: Parse the color values separated by commas
    while ((token = strtok(NULL, ", ")) != NULL && i < 3)
    {
        values[i++] = atoi(token); // Convert token to integer and store in values array
    }

    // Step 3: Check we have exactly 3 color components
    if (i != 3)
        return (FAILURE);

    // Step 4: Assign color values to the ambient_light structure
    ambient_light->colour.r = values[0];
    ambient_light->colour.g = values[1];
    ambient_light->colour.b = values[2];

    return (SUCCESS);
}
*/


/*
int parse_ambient_light(char *line, t_AmbientLight *ambient_light)
{
    char *token;
    float ratio;

    (void) line;
    printf(G "Entering" RST " parse_ambient_light()\n");
    
    // Parse the ratio token
    if (get_next_token(&token) == FAILURE)
        warn_err_exit("No token found", 1);
    
    ratio = parse_float(&token);
    if (ratio == FAILURE)
        err_exit(1);
    
    ambient_light->ratio = ratio;

    // Check the ratio bounds
    if (ambient_light->ratio < 0.0f || ambient_light->ratio > 1.0f)
        warn_err_exit("Ambient light ratio out of range (0.0 to 1.0)", 1);
    
    printf("\n   Parsed ratio: %f\n", ambient_light->ratio);

    // Parse the color token
    if (get_next_token(&token) == FAILURE)
        warn_err_exit("No token found", 1);
    
    // Call the parse_colour function
    if (parse_colour(token, &ambient_light->colour) == FAILURE)
        err_exit(1);

    // Check for any remaining tokens
    if (get_next_token(&token) == SUCCESS)
    {
        // If there's any valid content remaining in token, it indicates excess values
        if (token != NULL && strlen(token) > 0)
        {
            warn_err_exit("Excess ambient light values", 1);
        }
    }

    printf(G "   SUCCESS - Ambient Light parsed and added!\n\n");
    printf(RED "Exiting" RST " parse_ambient_light()\n\n");
    printf("---------------------------------------------------------------\n");
    
    return (SUCCESS);
}
*/
/*
// previous

int parse_ambient_light(char *line, t_AmbientLight *ambient_light)
{
    char *token;
    float ratio;

	(void)line;

    printf(G "Entering" RST " parse_ambient_light()\n");

    // Parse the ratio token
    if (get_next_token(&token) == FAILURE)
        warn_err_exit("No token found", 1);

    ratio = parse_float(&token);
    if (ratio == FAILURE)
        err_exit(1);

    ambient_light->ratio = ratio;

    // Check the ratio bounds
    if (ambient_light->ratio < 0.0f || ambient_light->ratio > 1.0f)
        warn_err_exit("Ambient light ratio out of range (0.0 to 1.0)", 1);

    printf("\n   Parsed ratio: %f\n", ambient_light->ratio);

    // Get the next token for the color
    if (get_next_token(&token) == FAILURE)
        warn_err_exit("No token found for color", 1);

    // Here, we need to handle any excess tokens after parsing the color
    char *color_token = strdup(token);  // Duplicate token to avoid modifying original

    // Call the parse_colour function
    if (parse_colour(color_token, &ambient_light->colour) == FAILURE)
        err_exit(1);

    // Check for remaining tokens in the line
    char *next_token;
    if (get_next_token(&next_token) == SUCCESS)
    {
        if (next_token != NULL && strlen(next_token) > 0)
        {
            printf(RED "\n   Warning! Excess ambient light values\n" RST);
            free(color_token);  // Free the duplicated token
            err_exit(1);
        }
    }

    printf(G "   SUCCESS - Ambient Light parsed and added!\n\n");
    printf(RED "Exiting" RST " parse_ambient_light()\n\n");
    printf("---------------------------------------------------------------\n");

    free(color_token);  // Free the duplicated token
    return (SUCCESS);
}
*/
/*
// TEST
int parse_ambient_light(char *line, t_AmbientLight *ambient_light)
{
    char token[MAX_TOKEN_LENGTH];

    printf(G "Entering" RST " parse_ambient_light()\n");

    // Pass &token instead of token
    char *token_ptr = token;  // Pointer to token
    if (get_next_token(&token_ptr, &line) == FAILURE || 
        (ambient_light->ratio = parse_float(&token_ptr)) == FAILURE ||
        ambient_light->ratio < 0.0f || ambient_light->ratio > 1.0f)
    {
        warn_err_exit("Invalid ambient light ratio", 1);
    }

    printf("\n   Parsed ratio: %f\n", ambient_light->ratio);

    // Parse color components
    for (int i = 0; i < 3; i++)
    {
        if (get_next_token(&token_ptr, &line) == FAILURE)
        {
            printf(RED "\n   Warning! Missing RGB colour value\n" RST);
            return FAILURE;
        }
        int color_value = parse_int(&token_ptr);
        if (color_value < 0 || color_value > 255)
        {
            printf(RED "\n   Warning! Colour value outside of range (0-255)\n" RST);
            return FAILURE;
        }
        if (i == 0) ambient_light->colour.r = color_value;
        else if (i == 1) ambient_light->colour.g = color_value;
        else ambient_light->colour.b = color_value;
    }

    printf("   Parsed colour: R = %d, G = %d, B = %d\n", 
           ambient_light->colour.r, 
           ambient_light->colour.g, 
           ambient_light->colour.b);

    printf(G "   SUCCESS - Ambient Light parsed and added!\n\n");
    printf(RED "Exiting" RST " parse_ambient_light()\n\n");

    return SUCCESS;
}
*/

// THIS ONE
int	parse_camera(char *line, t_Camera *camera)
{
	char	*token;

	(void) line;
	printf(G "Entering" RST " parse_camera()\n\n");
	if (get_next_token(&token) == FAILURE)
		return (printf("   Failed to get X position for camera\n"), 0);
	camera->position.x = atof(token);
	if (get_next_token(&token) == FAILURE)
		return (printf("   Failed to get Y position for camera\n"), 0);
	camera->position.y = atof(token);
	if (get_next_token(&token) == FAILURE)
		return (printf("   Failed to get Z position for camera\n"), 0);
	camera->position.z = atof(token);
	printf("   -> Parsed position: x = %f, y = %f, z = %f\n", camera->position.x,
		camera->position.y, camera->position.z);
	if (get_next_token(&token) == FAILURE)
		return (printf("   Failed to get X orientation for camera\n"), 0);
	camera->orientation.x = atof(token);
	if (get_next_token(&token) == FAILURE)
		return (printf("   Failed to get Y orientation for camera\n"), 0);
	camera->orientation.y = atof(token);
	if (get_next_token(&token) == FAILURE)
		return (printf("   Failed to get Z orientation for camera\n"), 0);
	camera->orientation.z = atof(token);
	printf("   -> Parsed orientation: x = %f, y = %f, z = %f\n",
		camera->orientation.x, camera->orientation.y, camera->orientation.z);
	if (get_next_token(&token) == FAILURE)
		return (printf("   Failed to get FOV for camera\n"), 0);
	camera->fov = atof(token);
	printf("   -> Parsed FOV: %f\n", camera->fov);
	if (camera->fov < 0 || camera->fov > 180)
		err_exit(7);
	printf(G "   SUCCESS - Camera parsed and added!\n\n");
	printf(RED "Exiting" RST " parse_camera()\n\n");
	printf("---------------------------------------------------------------\n");
	return (SUCCESS);
}

/*
int	parse_light(char *line, t_Light *light)
{
	char	*token;

	(void) line;
	printf(G "Entering" RST " parse_light()\n\n");
	//if (!get_next_token(&token))
	if (get_next_token(&token) == FAILURE)
		warn_err_exit("No token found", 1);
		//return (0);
		//err_exit(1);
	parse_vector3(token, &light->position);
	//if (!get_next_token(&token))
	if (get_next_token(&token) == FAILURE)
		warn_err_exit("No token found", 1);	
		//return (1);
		//err_exit(1);
	light->brightness = parse_float(&token);
	if (light->brightness < 0.0f || light->brightness > 1.0f)
		//err_exit("Light brightness ratio out of range (0.0 to 1.0)");
		//err_exit(6);
		warn_err_exit("Light brightness ratio out of range (0.0 to 1.0)", 1);
	printf("   Parsed brightness: %f\n", light->brightness);
	if (get_next_token(&token) == FAILURE)
	//if (!get_next_token(&token))
		//return (FAILURE);
		//err_exit(1);
		warn_err_exit("No token found", 1);
	//parse_colour(token, &light->colour);
	if (parse_colour(token, &light->colour) == FAILURE)
		err_exit(1);
	if (get_next_token(&token) == SUCCESS)
		warn_err_exit("Excess light values", 1);
	printf(G "   SUCCESS - Light parsed and added!\n\n");
	printf(RED "Exiting" RST " parse_light()\n\n");
	printf("---------------------------------------------------------------\n");
	return(SUCCESS); // changed from return (1)
}
*/


/*
// previous
int	parse_light(char *line, t_Light *light)
{
	char	*token;

	(void) line;
	printf(G "Entering" RST " parse_light()\n\n");
	if (get_next_token(&token) == FAILURE)
		warn_err_exit("No token found", 3);
	//if (parse_vector3(token, &light->position) == FAILURE)
	if (parse_vector3(&light->position) == FAILURE)
    	err_exit(3);
	if (get_next_token(&token) == FAILURE)
		warn_err_exit("No token found", 3);	
	light->brightness = parse_float(&token);
	if (light->brightness < 0.0f || light->brightness > 1.0f)
		warn_err_exit("Light brightness ratio out of range (0.0 to 1.0)", 3);
	printf("   Parsed brightness: %f\n", light->brightness);
	if (get_next_token(&token) == FAILURE)
		warn_err_exit("No token found", 3);
	if (parse_colour(token, &light->colour) == FAILURE)
		err_exit(3);
	if (get_next_token(&token) == SUCCESS)
		warn_err_exit("Excess light values", 3);
	printf(G "   SUCCESS - Light parsed and added!\n\n");
	printf(RED "Exiting" RST " parse_light()\n\n");
	printf("---------------------------------------------------------------\n");
	return (SUCCESS);
}
*/

int parse_light(char *line, t_Light *light)
{
    char *token;
    int i = 0;

    (void)line;
    printf(G "Entering" RST " parse_light()\n\n");

    // Get the token for the light position
    //if (get_next_token(&token) == FAILURE)
    //    warn_err_exit("No token found", 3);
    // Parse the light position using the updated parse_vector3
    if (parse_vector3(&light->position) == FAILURE)
        err_exit(3);
    // Get the token for the brightness
    if (get_next_token(&token) == FAILURE)
        warn_err_exit("No token found", 3);
    // Parse the brightness value
    light->brightness = parse_float(&token);
    if (light->brightness < 0.0f || light->brightness > 1.0f)
        warn_err_exit("Light brightness ratio out of range (0.0 to 1.0)", 3);
    printf("   -> Parsed brightness: %f\n", light->brightness);
   while (i < 3) // Expecting exactly 3 tokens for RGB
    {
        if (get_next_token(&token) == FAILURE)
            warn_err_exit("No more tokens found for RGB values", 1);

        int value = atoi(token); // Assuming parse_colour can handle int values.
        if (i == 0)
            light->colour.r = value;
        else if (i == 1)
            light->colour.g = value;
        else if (i == 2)
            light->colour.b = value;
        i++; // Increment the counter for each RGB value parsed
    }
	printf("   -> Parsed colour: R = %d, G = %d, B = %d\n", light->colour.r,
		light->colour.g, light->colour.b);
    if (get_next_token(&token) == SUCCESS)
        warn_err_exit("Excess light values", 3);

    printf(G "   SUCCESS - Light parsed and added!\n\n");
    printf(RED "Exiting" RST " parse_light()\n\n");
    printf("---------------------------------------------------------------\n");

    return (SUCCESS);
}

/*
// OG parse_camera
int	parse_camera(t_Camera *camera)
{
	char	*token;
	int		fov;

	printf(G "Entering" RST " parse_camera()\n\n");
	if (parse_position(&camera->position, &token) == FAILURE)
		err_exit(11);
	printf("\n   -> Parsed position: x = %f, y = %f, z = %f\n\n",
		camera->position.x, camera->position.y, camera->position.z);
	if (parse_orientation(&camera->orientation, &token) == FAILURE)
		err_exit(11);
	printf("\n   -> Parsed orientation: x = %f, y = %f, z = %f\n\n",
		camera->orientation.x, camera->orientation.y, camera->orientation.z);
	if (get_next_token(&token) == FAILURE)
		warn_err_exit("   Error! Failed to get FOV for camera", 11);
	fov = parse_int(&token);
	if (fov == FAILURE)
		err_exit(10);
	camera->fov = fov;
	if (camera->fov < 0 || camera->fov > 180)
		warn_err_exit("\n   Error! FOV out of range (0-180)", 11);
	printf("\n   -> Parsed FOV: %d\n\n", camera->fov);
	if (get_next_token(&token) == SUCCESS)
		warn_err_exit("\n   Error! Excess camera value(s)", 11);
	printf(G "   SUCCESS - Camera parsed and added!\n\n");
	printf(RED "Exiting" RST " parse_camera()\n\n");
	printf("---------------------------------------------------------------\n");
	return (SUCCESS);
}

// OG parse_light
int	parse_light(t_Light *light)
{
	char	*token;
	float	brightness;

	printf(G "Entering" RST " parse_light()\n\n");
	if (parse_vector3(&light->position) == FAILURE)
		warn_err_exit("\n   Error! Failed to get position for light point", 12);
	if (get_next_token(&token) == FAILURE)
		warn_err_exit("   No brightness value found", 12);
	brightness = parse_float(&token);
	if (brightness == FAILURE)
		warn_err_exit(" for brightness", 12);
	if (brightness < 0.0f || brightness > 1.0f)
		warn_err_exit("\n   Light brightness ratio out of range (0.0 to 1.0)",
			12);
	light->brightness = brightness;
	printf("\n   -> Parsed brightness: %f\n\n", light->brightness);
	if (parse_rgb(&light->colour, &token) == FAILURE)
		err_exit(12);
	if (get_next_token(&token) == SUCCESS)
		warn_err_exit("\n   Excess light value(s)", 12);
	printf(G "   SUCCESS - Light parsed and added!\n\n");
	printf(RED "Exiting" RST " parse_light()\n\n");
	printf("---------------------------------------------------------------\n");
	return (SUCCESS);
}
*/
