/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:03:15 by atang             #+#    #+#             */
/*   Updated: 2024/10/11 14:03:06 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
- read_and_append_lines reads and appends lines from a 'fd' to the 'stash' 
buffer until it finds a newline character or reaches the end of the file.
- fn dynamically allocates memory for 'temp_buffer' to read chunks of data, 
and 'bytes_read' is initialised to 1 so we enter the while loop to read data
- Inside the loop, as long as there is no newline character in the stash AND 
'bytes_read' is not 0 (i.e. end of file has been reached so no more to read):
	- data is read from the 'fd' into the 'temp_buffer' up to 'buffer_size' 
	of data
	- if an error occurs during read (i.e. return of -1), memory is freed and 
	NULL is returned
	- null-terminator is added at the end of the data read to turn it into 
	a null-terminated string
	- if the 'stash' buffer is empty (NULL), it is initialised using 
	gnl_initialise_str to allocate memory for an empty string
	- data read from 'temp_buffer' is appended to the 'stash' buffer using
	gnl_strjoin, accumulating data into the 'stash' buffer
	- if memory allocation for 'stash' during gnl_strjoin failed, error has 
	occured so break to exit loop
- 'temp_buffer' is freed and the updated 'stash' buffer with accumulated data
read from the 'fd' is returned
 */
char	*read_and_append_lines(int fd, char	*stash)
{
	char	*temp_buffer;
	int		bytes_read;

	temp_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp_buffer)
		return (NULL);
	bytes_read = 1;
	while (!gnl_strchr(stash, '\n') && (bytes_read != 0))
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(stash);
			free(temp_buffer);
			return (NULL);
		}
		temp_buffer[bytes_read] = '\0';
		if (!stash)
			stash = gnl_initialise_str();
		stash = gnl_strjoin(stash, temp_buffer);
		if (!stash)
			break ;
	}
	free(temp_buffer);
	return (stash);
}

/* 
- extract_line_from_stash extracts a line from the 'stash' buffer until a 
newline character is found
- fn checks if the 'stash' buffer is empty, if it is then there is no line 
to extract so NULL is returned
- length needed to be extracted is calculated by iterating i through 'stash' 
buffer while not '\0' OR '\n'
- after determining length of the line, memory is dynamically allocated 
for the 'extracted_line' (+2 to accommodate '\n' AND '\0'). If memory 
allocation failed, NULL is returned to indicate an error has occurred
- once memory has been allocated successfullly, a while loop is entered where
characters are copied FROM the 'stash' buffer INTO the 'extracted_line' until
the '\n' is found or the end of the the 'stash' buffer is reached
- after copying, the fn checks if the character at the current position 
in the 'stash' buffer is '\n', and if it is, the '\n' is also copied into 
'extracted_line' so that '\n' is also in 'extracted_line'
- 'extracted_line' is null-terminated as a str should be and then returned 
containing the extracted line from the 'stash' buffer 
*/

char	*extract_line_from_stash(char	*stash)
{
	char	*extracted_line;
	int		i;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	extracted_line = (char *)malloc(sizeof(char) * (i + 2));
	if (!extracted_line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		extracted_line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		extracted_line[i] = stash[i];
		i++;
	}
	extracted_line[i] = '\0';
	return (extracted_line);
}

/* 
- remaining_stash returns the remaining contents of the 'stash' buffer 
after extracting a line
- fn uses a while loop to iterate through the 'stash' buffer until either
'\0' or '\n' (to find the end of the 'stash' buffer or the position of 
the newline character)
- fn then checks if it is at the end of the 'stash' buffer (i.e. no more 
characters in the buffer), and if it is, the 'stash' buffer has been 
processed completely so there is no more data to extract. In that case, 
'stash' is freed and NULL is returned to denote no remaining data
- if the 'stash' buffer isn't fully processed, the fn then calculates the 
length of the remaining data in the 'stash' (from newline character position
to the end) and allocates memory for the 'remaining' buffer to store the 
data. If memory allocation fails for 'remaining', NULL is returned
- s_index is incremented to move PAST '\n' in the 'stash' and another while
loop is entered to copy the remaining data FROM the 'stash' buffer INTO the
'remaining' buffer until the end of the 'stash' buffer
- '\0' is added to the end of 'remaining' buffer, 'stash' is freed, and the
'remaining' buffer is returned which has the remaining data from 'stash' 
after line extraction
 */

char	*remaining_stash_after_extraction(char *stash)
{
	int		s_index;
	int		r_index;
	char	*remaining;

	s_index = 0;
	r_index = 0;
	if (!stash)
		return (NULL);
	while (stash[s_index] && stash[s_index] != '\n')
		s_index++;
	if (!stash[s_index])
	{
		free(stash);
		return (NULL);
	}
	remaining = (char *)malloc(sizeof(char) * ((gnl_strlen(stash)
					- s_index + 1)));
	if (!remaining)
		return (NULL);
	s_index++;
	while (stash[s_index])
		remaining[r_index++] = stash[s_index++];
	remaining[r_index] = '\0';
	free(stash);
	return (remaining);
}

/*
get_next_line() reads from a fd and returns the next line as a 
string. It uses a static variable, stash, to store the remaining 
data from previous reads. It first checks if the fd is valid and 
if the buffer size is >= 0. If so, and stash != NULL, 
extract_line_from_stash() is called to extract a line from the 
stash. Then, remaining_stash_after_extraction() is called to get 
the remaining data in the stash after line extraction. If a line was 
successfully extracted, it is assigned to the line parameter and 
returned. 
*/

char	*get_next_line(int fd, char **line)
{
	static char	*stash;
	char		*completed_line_or_null;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (stash)
			free(stash);
		return (NULL);
	}
	stash = read_and_append_lines(fd, stash);
	if (!stash)
	{
		free(stash);
		return (NULL);
	}
	completed_line_or_null = extract_line_from_stash(stash);
	stash = remaining_stash_after_extraction(stash);
	if (completed_line_or_null)
	{
		*line = completed_line_or_null;
		return (*line);
	}
	free(stash);
	return (completed_line_or_null);
}
