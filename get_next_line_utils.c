/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytolstob <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:35:26 by ytolstob          #+#    #+#             */
/*   Updated: 2024/06/25 19:09:32 by ytolstob         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <stddef.h>

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;
	char	srch;

	i = 0;
	str = (char *)s;
	srch = (char)c;
	while (str[i] != srch)
	{
		if (str[i] == '\0')
			return (0);
		i++;
	}
	return (str + i);
}

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		i;
	int		len;

	i = 0;
	if (!src)
		return (NULL);
	len = ft_strlen(src);
	dest = (char *)malloc(len + 1);
	if (dest == NULL)
		return (NULL);
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	char	*dest;

	i = 0;
	if (!src)
		return (NULL);
	dest = (char *)malloc(n + 1);
	if (dest == NULL)
		return (NULL);
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*res;
	int		size;

	size = (ft_strlen(s1) + ft_strlen(s2) + 1);
	res = (char *)malloc(sizeof(char) * size);
	if (res == NULL)
		return (NULL);
	ft_strcpy(res, s1);
	ft_strcat(res, s2);
	return (res);
}

char	*extract_line_from_remainder(char **remainder)
{
	char	*newline_pos;
	char	*line;
	char	*new_remainder;
	int	len;

	if (!*remainder)
		return (NULL);
	newline_pos = ft_strchr(*remainder, '\n');
	if (newline_pos)
	{
		line = ft_strndup(*remainder, newline_pos - *remainder + 1);
		new_remainder = ft_strdup(newline_pos + 1);
		free(*remainder);
		*remainder = new_remainder;
		return (line);
	}
	len = ft_strlen(*remainder);
	if (len > 0)
	{
		line = ft_strdup(*remainder);
		free(*remainder);
		*remainder = NULL;
		return (line);
	}
	return (NULL);
}

char	*join_remainder(char *remainder, const char *buffer)
{
	char	*new_remainder;

	if (!remainder)
		return (ft_strdup(buffer));
	new_remainder = malloc(ft_strlen(remainder) + ft_strlen(buffer) + 1);
	if (!new_remainder)
		return (NULL);
	ft_strcpy(new_remainder, remainder);
	ft_strcat(new_remainder, buffer);
	free(remainder);
	return (new_remainder);
}
