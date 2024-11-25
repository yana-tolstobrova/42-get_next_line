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

#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;
	char		buffer[BUFFER_SIZE + 1];
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (remainder)
	{
		line = extract_line_from_remainder(&remainder);
		if (line)
			return (line);
	}
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		remainder = join_remainder(remainder, buffer);
		if (!remainder)
			return (NULL);
		line = extract_line_from_remainder(&remainder);
		if (line)
			return (line);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read == 0 && remainder && *remainder)
	{
		line = ft_strdup(remainder);
		free(remainder);
		remainder = NULL;
		return (line);
	}
	free(remainder);
	remainder = NULL;
	return (NULL);
}

int	main(void)
{
	char	*line;
	//int		fd;

	//fd = open("test.txt", O_RDONLY);
	line = get_next_line(1);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(1);
	}
	//if (fd != 0)
	//	close(1);
	return (0);
}
