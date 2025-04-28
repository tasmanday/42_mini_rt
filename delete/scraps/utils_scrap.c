
/*
--> WORKING OG get_net_token
int	get_next_token(char **token)
{
	*token = strtok(NULL, " ,\t\n");
	while (*token && **token == '\0') // Skip empty tokens if any
    {
        *token = strtok(NULL, " \t\n");

    }
	if (!*token)
	{
		return (FAILURE);
	}
	printf("   Token: %s\n", *token);
	return (SUCCESS);
}
*/

char *ft_strtok(char **line, const char *delim)
{
    char *start;
    
    if (line == NULL || *line == NULL)
	{
		//printf("If last == NULL of the content is NULL\n");
		return (NULL);
	}
    while (**line && strchr(delim, **line))
	{
        //printf("Skipping delimiter: '%s'\n", *line);
		(*line)++;
    }
    if (**line == '\0')
	{
		//printf("End of string reached after skipping delimiters\n");
        *line = NULL;
        return (NULL);
    }
    start = *line;
	//printf("\nStart of token: '%s'\n", start);
    while (**line && !strchr(delim, **line)) // find end of token
	{
        (*line)++;
    }
    if (**line)
	{
		//printf("Delimiter found: '%c'\n", **line);
        **line = '\0';
        (*line)++;  // Move past the delimiter
    }
	else
	{
		//printf("End of string reached while parsing token\n");
        *line = NULL;  // No more tokens
    }
	//printf("Returning token: '%s'\n", start);
    return (start);
}

/*
size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
*/