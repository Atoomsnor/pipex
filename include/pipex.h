/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:28:58 by roversch          #+#    #+#             */
/*   Updated: 2025/03/24 18:14:30 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"

/* Error Handling */
void	die(const char *msg, int exit_code, int fds[3]);

/* Process Management */
void	parent(char **argv, char **paths, char **envp);
void	child1(char **argv, int *pipe_fd, char **paths, char **envp);
void	child2(char **argv, int *pipe_fd, char **paths, char **envp);

/* Path Handling */
char	**split_paths(char **envp);
char	*find_path(char **paths, char *cmd);
void	free_paths(char **paths);

/* Main Function */
int		main(int argc, char **argv, char **envp);

#endif