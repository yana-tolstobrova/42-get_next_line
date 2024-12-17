/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytolstob <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 23:27:41 by ytolstob          #+#    #+#             */
/*   Updated: 2024/11/25 23:27:46 by ytolstob         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

char	*extract_line(char **remainder, char *newline_pos)
{
	char	*line;
	char	*new_remainder;
	size_t	line_len;

	line = NULL;
	line_len = newline_pos - *remainder + 1;
	line = ft_strndup(*remainder, line_len);
	if (!line)
		return (NULL);
	if (*(newline_pos + 1) != '\0')
		new_remainder = ft_strdup(newline_pos + 1);
	else
		new_remainder = NULL;
	if (!new_remainder && *(newline_pos + 1) != '\0')
	{
		free(line);
		return (NULL);
	}
	free(*remainder);
	*remainder = new_remainder;
	return (line);
}

char	*extract_line_from_remainder(char **remainder)
{
	char	*newline_pos;
	char	*line;

	line = NULL;
	if (!*remainder || !**remainder)
		return (NULL);
	newline_pos = ft_strchr(*remainder, '\n');
	if (newline_pos)
	{
		line = extract_line(remainder, newline_pos);
	}
	else
	{
		line = ft_strdup(*remainder);
		free(*remainder);
		*remainder = NULL;
	}
	return (line);
}

int	read_and_join(int fd, char **remainder, char *buffer)
{
	int		bytes_read;
	char	*new_remainder;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (bytes_read);
	buffer[bytes_read] = '\0';
	new_remainder = ft_strjoin(*remainder, buffer);
	if (!new_remainder)
		return (-1);
	*remainder = new_remainder;
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*remainder = NULL;
	char		*buffer;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 0;
	while (!ft_strchr(remainder, '\n'))
	{
		bytes_read = read_and_join(fd, &remainder, buffer);
		if (bytes_read <= 0)
			break ;
	}
	free(buffer);
	if (bytes_read < 0 || !remainder)
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	return (extract_line_from_remainder(&remainder));
}

//int   main(void)
// {
//  	char    *line;
//     int           fd;
//
//     fd = open("test.txt", O_RDONLY);
//     line = get_next_line(fd);
// 	// line = get_next_line(1);
//     while (line)
//     {
//     	printf("%s", line);
//         free(line);
//         line = get_next_line(fd);
//         // line = get_next_line(1);
//     }
//     if (fd != 0)
//         close(fd);
// 	// close(1);
//     return (0);
//}
