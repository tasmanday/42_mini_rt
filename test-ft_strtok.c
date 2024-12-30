#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char    *ft_strtok(char *str, const char *delim)
{
    static char *next_token = NULL;
    char        *token_start;

    if (str != NULL) {
        next_token = str;
    }
    else if (next_token == NULL)
    {
        return NULL;
    }
    while (*next_token != '\0' && strchr(delim, *next_token) != NULL)
    {
        next_token++;
    }
    if (*next_token == '\0')
    {
        next_token = NULL;
        return NULL;
    }
    token_start = next_token;
    while (*next_token != '\0' && strchr(delim, *next_token) == NULL) {
        next_token++;
    }
    if (*next_token != '\0')
    {
        *next_token = '\0';
        next_token++;
    }
    else
    {
        next_token = NULL;
    }
    return (token_start);
}

int main(void)
{
    char line[] = "A 0.2 255,255,255        ,";
    char *token = ft_strtok(line, " ,\t\n\r");
    while (token != NULL)
    {
        printf("Token: '%s'\n", token);
        token = ft_strtok(NULL, " ,\t\n\r");
    }
    return (0);
}
