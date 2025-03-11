/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:20:30 by roversch          #+#    #+#             */
/*   Updated: 2025/02/24 15:04:28 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef enum t_file_status
{
	READ_ERROR = -1,
	READ_EOF = 0,
}	t_file_status;

char	*get_the_line(int fd, char *leftover, char *buffer);
char	*store_leftovers(char **line);
char	*get_next_line(int fd);
size_t	gnl_strlen(const char *s);
char	*gnl_strjoin(char const *s1, char const *s2);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
char	*gnl_strdup(const char *s);
char	*gnl_strchr(char *s, int c);

#endif