/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytolstob <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:48:40 by ytolstob          #+#    #+#             */
/*   Updated: 2024/07/21 15:53:43 by ytolstob         ###   ########.fr       */
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

	line = NULL;
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
		remainder = join_remainder(remainder, buffer + 1);
		line = extract_line_from_remainder(&remainder);
		if (line)
			return (line);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read == 0 && remainder && *remainder)
	{
		line = remainder;
		remainder = NULL;
		return (line);
	}
	free(remainder);
	remainder = NULL;
	return (NULL);
}

//int	main(void)
//{
//	char	*line;
//	int		fd;
//
//	fd = open("test.txt", O_RDONLY);
//	line = get_next_line(fd);
//	while (line)
//	{
//		printf("%s", line);
//		free(line);
//		line = get_next_line(fd);
//	}
//	if (fd != 0)
//		close(fd);
//	return (0);
//}
