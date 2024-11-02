/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:24:03 by atang             #+#    #+#             */
/*   Updated: 2024/11/02 13:30:30 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	parse_float()
	Converts a str to float and updates the string pointer to point at the next 
	part of the string after the converted number
*/

/*
float	parse_float(char **str)
{
	char	*end;
	float	result;

	result = strtof(*str, &end);
	if (end == *str)
	{
		printf(RED"\n   Warning! No valid float found in '%s'\n"RST, *str);
		return (FAILURE);
		//return (0.0f);
	}
	//printf("Parsed float: %f, remaining after float: '%s'\n", result, end);
	if (*end != '\0' && !ft_isspace(*end) && *end != ',') // Added && part
	{
		printf(RED"\n   Warning! Invalid characters within float in '%s'\n"RST, *str);
		return (FAILURE);
	}
	*str = end;
	while (**str == ' ' || **str == '\t' || **str == ',')
		(*str)++;
	return (result);
}
*/

/*
// previous
float parse_float(char **str)
{
    char *end;
    float result;

    // Skip past the 'A' identifier
    if (**str == 'A' || **str == ' ' || **str == '\t' || **str == ',')
	{
		while (**str == 'A' || **str == ' ' || **str == '\t' || **str == ',') 
		{
			(*str)++; // Move past the 'A'
		}
	}
    result = strtof(*str, &end);
    if (end == *str) {
        printf(RED "\n   Warning! No valid float found in '%s'\n" RST, *str);
        return FAILURE;
    }

    if (*end != '\0' && !ft_isspace(*end) && *end != ',') {
        printf(RED "\n   Warning! Invalid characters within float in '%s'\n" RST, *str);
        return FAILURE;
    }

    *str = end;
    while (**str == ' ' || **str == '\t' || **str == ',') {
        (*str)++;
    }

    return result;
}
*/
float parse_float(char **str)
{
    char *end;
    float result;

    // Skip initial spaces, tabs, or commas
    while (**str == ' ' || **str == '\t' || **str == ',') 
    {
        (*str)++;
    }

    // Parse the float, including handling negative signs
    result = strtof(*str, &end);
    if (end == *str) {
        printf(RED "\n   Warning! No valid float found in '%s'\n" RST, *str);
        return FAILURE;
    }

    // Check for invalid characters after the number
    if (*end != '\0' && !ft_isspace(*end) && *end != ',') {
        printf(RED "\n   Warning! Invalid characters within float in '%s'\n" RST, *str);
        return FAILURE;
    }

    *str = end;  // Move the string pointer to the end of the parsed float

    // Skip any additional spaces, tabs, or commas
    while (**str == ' ' || **str == '\t' || **str == ',') {
        (*str)++;
    }

    return result;
}
                                                                                              
/*
	parse_int()
	Converts a str to int and updates the string pointer to point at the next 
	part of the string after the converted number
*/

int	parse_int(char	**str)
{
	char	*end;
	int		result;

	result = (int)strtol(*str, &end, 10);
	if (end == *str)
		return (0);
	if (*end == ',' || *end == '\0' || *end == ' ' || *end == '\t')
		*str = end + 1;
	else
		*str = end;
	return (result);
}

/*
	parse_vector3()
	Converts 3 floating-point numbers from a str and assigns them to the Vector3 
	structure's x, y, and z components. Each call to parse_float updates the str 
	pointer to point at the next part of the string
*/

/*
int	parse_vector3(char *str, t_Vector3 *vec)
{
	//printf("   Parsing vector from: %s\n", str);
	vec->x = parse_float(&str);
	vec->y = parse_float(&str);
	vec->z = parse_float(&str);
	printf("   Parsed vector: x = %f, y = %f, z = %f\n", vec->x,
		vec->y, vec->z);
	//return (1);
	return (SUCCESS);
}
*/

/*
// PREVIOUS
int	parse_vector3(char *str, t_Vector3 *vec)
{
	float x_value;
	float y_value;
	float z_value;

	x_value = parse_float(&str);
	if (x_value == FAILURE)
		return (FAILURE);
	y_value = parse_float(&str);
	if (y_value == FAILURE)
		return (FAILURE);
	z_value = parse_float(&str);
	if (z_value == FAILURE)
		return (FAILURE);
	vec->x = x_value;
	vec->y = y_value;
	vec->z = z_value;
	printf("   Parsed vector: x = %f, y = %f, z = %f\n", vec->x,
		vec->y, vec->z);
	return (SUCCESS);
}
*/

int parse_vector3(t_Vector3 *vec)
{
    char *token;
    float x_value, y_value, z_value;

    // Get the token for the x value
    if (get_next_token(&token) == FAILURE)
        return (FAILURE);
    x_value = parse_float(&token);
    if (x_value == FAILURE)
        return (FAILURE);

    // Get the token for the y value
    if (get_next_token(&token) == FAILURE)
        return (FAILURE);
    y_value = parse_float(&token);
    if (y_value == FAILURE)
        return (FAILURE);

    // Get the token for the z value
    if (get_next_token(&token) == FAILURE)
        return (FAILURE);
    z_value = parse_float(&token);
    if (z_value == FAILURE)
        return (FAILURE);

    // Assign the parsed values to the vector
    vec->x = x_value;
    vec->y = y_value;
    vec->z = z_value;
    printf("   Parsed vector: x = %f, y = %f, z = %f\n", vec->x, vec->y, vec->z);

    return (SUCCESS);
}




/*
	parse_colour()
	Converts 3 int numbers from a str and assigns them to the Colour structure's 
	r, g, and b components
*/

/*
int	parse_colour(char *str, t_Colour *colour)
{
	colour->r = parse_int(&str);
	colour->g = parse_int(&str);
	colour->b = parse_int(&str);
	if (!colour->r || !colour->g || !colour->b)
	{
		printf(RED"\n   Warning! Missing RBG colour value\n"RST);
		return(FAILURE);
	}
	if (colour->r < 0 || colour->r > 255
		|| colour->g < 0 || colour->g > 255
		|| colour->b < 0 || colour->b > 255)
	{
		printf(RED"\n   Warning! Colour value outside of range (0-255)\n"RST);
		return (FAILURE);
	}
	printf("   Parsed colour: R = %d, G = %d, B = %d\n", colour->r,
		colour->g, colour->b);
	return (SUCCESS);
}
*/


int parse_colour(char *str, t_Colour *colour)
{
    char *token = str;
    int values[3];
    int i = 0;
    
    // Parse each RGB component separately
    while (i < 3)
    {
        if (get_next_token(&token) == FAILURE)
        {
            printf(RED"\n   Warning! Missing RGB colour value\n"RST);
            return (FAILURE);
        }
        
        // Convert token to integer
        char *endptr;
        long val = strtol(token, &endptr, 10);
        
        // Validate conversion
        if (*endptr != '\0' && !ft_isspace(*endptr) && *endptr != ',')
        {
            printf(RED"\n   Warning! Invalid RGB value: %s\n"RST, token);
            return (FAILURE);
        }
        
        // Validate range
        if (val < 0 || val > 255)
        {
            printf(RED"\n   Warning! Colour value outside of range (0-255): %ld\n"RST, val);
            return (FAILURE);
        }
        
        values[i++] = (int)val;
    }
    
    // Check for extra tokens
    if (get_next_token(&token) == SUCCESS)
    {
        printf(RED"\n   Warning! Extra RGB values detected\n"RST);
        return (FAILURE);
    }
    
    // Assign the values to the colour structure
    colour->r = values[0];
    colour->g = values[1];
    colour->b = values[2];
    
    printf("   Parsed colour: R = %d, G = %d, B = %d\n", 
           colour->r, colour->g, colour->b);
    return (SUCCESS);
}


/*
int parse_colour(char *str, t_Colour *colour)
{
    char *colour_token;
    int i = 0;
    int values[3];

    // Tokenize the string based on commas or spaces
    colour_token = strtok(str, ", ");
    while (colour_token != NULL)
    {
        // Parse the integer value
        values[i] = parse_int(&colour_token);
        
        // Check if parsing was successful
        if (values[i] == FAILURE)
        {
            printf(RED "\n   Warning! Invalid RGB value\n" RST);
            return (FAILURE);
        }

        // Increment the index for the next color component
        i++;

        // Check if we've exceeded the number of color components
        if (i > 3)
        {
            printf(RED "\n   Warning! Excess RGB colour values\n" RST);
            return (FAILURE);
        }

        // Move to the next token
        colour_token = strtok(NULL, ", ");
    }

    // Check if exactly three values were parsed
    if (i != 3)
    {
        printf(RED "\n   Warning! Missing RGB colour value\n" RST);
        return (FAILURE);
    }

    // Assign parsed values to the colour struct
    colour->r = values[0];
    colour->g = values[1];
    colour->b = values[2];

    // Validate the RGB range (0 to 255)
    if (colour->r < 0 || colour->r > 255 ||
        colour->g < 0 || colour->g > 255 ||
        colour->b < 0 || colour->b > 255)
    {
        printf(RED "\n   Warning! Colour value outside of range (0-255)\n" RST);
        return (FAILURE);
    }

    printf("   Parsed colour: R = %d, G = %d, B = %d\n", colour->r, colour->g, colour->b);
    return (SUCCESS);
}
*/


/*
char *ft_strtok(char *str, const char *delimiters) {
    static char *saved_str = NULL; // Static variable to keep track of position
    char *token_start;

    // If str is not NULL, initialize saved_str with the new string
    if (str != NULL) {
        saved_str = str; // Start with a new string
    }

    // If saved_str is NULL, there are no more tokens
    if (saved_str == NULL) {
        return NULL;
    }

    // Skip leading delimiters
    while (*saved_str && strchr(delimiters, *saved_str)) {
        saved_str++; // Move to the next character
    }

    // If we reached the end of the string, return NULL
    if (*saved_str == '\0') {
        return NULL;
    }

    // Set the start of the token
    token_start = saved_str;

    // Move saved_str to the end of the token
    while (*saved_str && !strchr(delimiters, *saved_str)) {
        saved_str++; // Move forward until we find a delimiter
    }

    // If we hit a delimiter, replace it with a null terminator
    if (*saved_str) {
        *saved_str = '\0'; // Null-terminate the token
        saved_str++; // Move past the null terminator for the next call
    }

    return token_start; // Return the extracted token
}
*/

/*
int get_next_token(char **token, char **line) {
    // Skip any leading whitespace
    while (**line == ' ' || **line == '\t') {
        (*line)++;
    }

    // Check if we've reached the end of the line
    if (**line == '\0') {
        return FAILURE;  // No more tokens
    }

    char *start = *line;  // Start of the token

    // Find the end of the token
    while (**line && **line != ',' && **line != ' ' && **line != '\t') {
        (*line)++;
    }

    // Calculate token length
    size_t token_length = *line - start;

    // Check token length and ensure it does not exceed the maximum allowed size
    if (token_length >= MAX_TOKEN_LENGTH) {
        printf("Warning! Token length exceeded max size\n");
        return FAILURE;  // Token is too long
    }

    // Copy the token to the provided buffer
    strncpy(*token, start, token_length);
    (*token)[token_length] = '\0';  // Null-terminate the token

    // Move past any following comma or whitespace
    if (**line == ',') {
        (*line)++;  // Skip the comma
    }
    // Skip any trailing whitespace
    while (**line == ' ' || **line == '\t') {
        (*line)++;
    }

    return SUCCESS;  // Token successfully extracted
}
*/

// NEWEST
int	get_next_token(char **token)
{
	*token = strtok(NULL, " \t,");
	if (!*token)
	{
		return (FAILURE);
	}
	printf("   Token: %s\n", *token);
	return (SUCCESS);
}

/*
int get_next_token(char **token, char **line) {
    // Skip any leading whitespace or commas
    while (**line == ' ' || **line == '\t' || **line == ',') {
        (*line)++;
    }

    // Skip past the identifier 'A'
    if (**line == 'A') {
        (*line)++; // Move past the identifier 'A'
    }

    // Check if we've reached the end of the line or encounter an empty line
    if (**line == '\0' || **line == '\n') {
        printf("Warning! End of line reached or empty line\n");
        return FAILURE;  // No more tokens or empty line
    }

    char *start = *line;  // Start of the token

    // Find the end of the token
    while (**line && **line != ',' && **line != ' ' && **line != '\t') {
        (*line)++;
    }

    // Calculate token length
    size_t token_length = *line - start;

    // Check token length and ensure it does not exceed the maximum allowed size
    if (token_length >= MAX_TOKEN_LENGTH) {
        printf("Warning! Token length exceeded max size\n");
        return FAILURE;  // Token is too long
    }

    // Copy the token to the provided buffer
    strncpy(*token, start, token_length);
    (*token)[token_length] = '\0';  // Null-terminate the token

    printf("Extracted token: %s\n", *token);

    // Move past any following comma, space, or tab
    while (**line == ',' || **line == ' ' || **line == '\t') {
        (*line)++;
    }

    return SUCCESS;  // Token successfully extracted
}
*/

/*
int	get_next_token(char **token, const char *delim)
{
	*token = strtok(NULL, delim);
	if (!*token)
	{
		return (FAILURE);
	}
	printf("Token: %s\n", *token);
	return (SUCCESS);
}
*/

/*
int get_next_token(char **token, const char *delim) {
    // Use strtok to continue tokenization
    *token = strtok(NULL, delim);
    if (!*token) {
        return FAILURE;
    }
    printf("Extracted Token: %s\n", *token); // Debug line
    return SUCCESS;
}
*/

/*
int get_next_token(char **token)
{
    static char *last_position = NULL;
    char *current_token;
    
    // If we're starting a new string (first call)
    if (*token != NULL && **token != '\0')
    {
        last_position = *token;
        current_token = strtok(last_position, " \t\n,");
    }
    else
    {
        // Continue tokenizing from last position
        current_token = strtok(NULL, " \t\n,");
    }
    
    // If no more tokens found
    if (!current_token)
    {
        *token = NULL;
        return (FAILURE);
    }
    
    // Update token pointer and return success
    *token = current_token;
    printf("Token: %s\n", *token);
    return (SUCCESS);
}
*/

int parse_rgb(t_Colour *colour, char **token)
{
    int i;
    int value;

    i = 0;
    while (i < 3)
    {
        if (get_next_token(token) == FAILURE || *token == NULL) 
            warn_err_exit("No more tokens found for RGB values", 1);
        value = atoi(*token);
        if (value < 0 || value > 255)
        {
            warn_err_exit("RGB value out of range (0-255)", 1);
        }
        if (i == 0)
            colour->r = value;
        else if (i == 1)
            colour->g = value;
        else if (i == 2) 
            colour->b = value;
        i++;
    }
    return (SUCCESS);
}

