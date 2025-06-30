/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtarvain <jtarvain@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:26:42 by jtarvain          #+#    #+#             */
/*   Updated: 2025/06/09 18:26:44 by jtarvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	char		*stash;
	size_t		new;
	ssize_t		bytes_read;

	stash = NULL;
	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!find_line(fd, buffer, &stash, &bytes_read))
	{
		if (stash)
			free(stash);
		return (NULL);
	}
	if (!stash && bytes_read == 0)
		return (NULL);
	if (!extract_line(&line, &stash, buffer))
		return (NULL);
	new = found_line(buffer);
	if (new > 0)
		ft_memcpy(buffer, buffer + new, ft_strlen(buffer + new) + 1);
	else
		buffer[0] = '\0';
	return (line);
}

int		find_line(int fd, char *buffer, char **stash, ssize_t *bytes_read)
{
	*bytes_read = 1;
	if (buffer[0] && found_line(buffer))
		return (1);
	while (*bytes_read > 0)
	{
		if (found_line(buffer))
			return (1);
		if (buffer[0])
		{
			*stash = strjoin_free(*stash, buffer);
			if (!*stash)
				return (0);
			buffer[0] = '\0';
		}
		*bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (*bytes_read == -1)
			return (0);
		if (*bytes_read == 0)
			return (1);
		buffer[*bytes_read] = '\0';
	}
	return (1);
}

char	*strjoin_free(char *stash, const char *buffer)
{
	char	*str;

	str = NULL;
	if (!stash)
		return (ft_strdup(buffer));
	else
	{
		str = ft_strjoin(stash, buffer);
		if (!str)
		{
			free(stash);
			return (NULL);
		}
		free(stash);
	}
	return (str);
}

int		extract_line(char **line, char **stash, const char *buffer)
{
	size_t	newline;
	char	*sub;

	newline = found_line(buffer);
	if (!newline)
	{
		*line = strjoin_free(*stash, buffer);
		*stash = NULL;
		return (1);
	}
	sub = ft_substr(buffer, 0, newline);
	if (!sub)
		return (free(*stash), 0);
	*line = strjoin_free(*stash, sub);
	free(sub);
	if (!*line)
		return (0);
	*stash = NULL;
	return (1);
}

size_t		found_line(const char *s)
{
	size_t	i;

	i = 0;
	while (1)
	{
		if (s[i] == '\n')
			return (i + 1);
		if (s[i] == 0)
			break ;
		i++;
	}
	return (0);
}
