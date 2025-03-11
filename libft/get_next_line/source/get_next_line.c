/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:20:22 by roversch          #+#    #+#             */
/*   Updated: 2025/02/24 15:04:03 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

char	*get_the_line(int fd, char *leftovers, char *buffer)
{
	ssize_t	bytes_read;
	char	*temp_leftovers;

	bytes_read = 1;
	while (bytes_read > 0 && !gnl_strchr(leftovers, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == READ_ERROR)
			return (free(leftovers), NULL);
		if (bytes_read == READ_EOF)
			break ;
		buffer[bytes_read] = '\0';
		if (!leftovers)
			leftovers = gnl_strdup("");
		if (!leftovers)
			return (NULL);
		temp_leftovers = leftovers;
		leftovers = gnl_strjoin(temp_leftovers, buffer);
		free(temp_leftovers);
		if (!leftovers)
			return (NULL);
	}
	return (leftovers);
}

char	*store_leftovers(char **line)
{
	char	*leftovers;
	char	*temp_line;
	size_t	i;

	i = 0;
	if (!*line)
		return (NULL);
	while ((*line)[i] != '\n' && (*line)[i] != '\0')
		i++;
	if ((*line)[i] == '\0')
		return (NULL);
	leftovers = gnl_substr(*line, i + 1, gnl_strlen(*line) - i - 1);
	if (!leftovers)
		return (NULL);
	temp_line = gnl_substr(*line, 0, i + 1);
	if (*leftovers == '\0' || !temp_line)
	{
		free(leftovers);
		leftovers = NULL;
	}
	free(*line);
	*line = temp_line;
	return (leftovers);
}

char	*get_next_line(int fd)
{
	static char	*leftovers;
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = get_the_line(fd, leftovers, buffer);
	if (!line)
	{
		leftovers = NULL;
		return (NULL);
	}
	leftovers = store_leftovers(&line);
	return (line);
}
