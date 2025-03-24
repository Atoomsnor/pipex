/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:38:15 by roversch          #+#    #+#             */
/*   Updated: 2025/03/24 18:15:37 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>

void	die(const char *msg, int exit_code, int fds[3])
{
	if (fds)
	{
		close(fds[0]);
		close(fds[1]);
		close(fds[2]);
	}
	perror(msg);
	exit(exit_code);
}

void	child1(char **argv, int *pipe_fd, char **paths, char **envp)
{
	int		infile;
	char	*full_path;
	char	**cmd1;

	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		die("infile Error", 1, (int []){pipe_fd[0], pipe_fd[1], infile});
	cmd1 = ft_split(argv[2], ' ');
	if (!cmd1)
		die("malloc failed", 1, (int []){pipe_fd[0], pipe_fd[1], infile});
	full_path = find_path(paths, cmd1[0]);
	if (!full_path)
		die("no found path", 127, (int []){pipe_fd[0], pipe_fd[1], infile});
	dup2(infile, STDIN_FILENO);
	close(infile);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	execve(full_path, cmd1, envp);
	die("execve failed", 126, (int []){pipe_fd[0], pipe_fd[1], infile});
}

void	child2(char **argv, int *pipe_fd, char **paths, char **envp)
{
	int		outfile;
	char	*full_path;
	char	**cmd2;

	close(pipe_fd[1]);
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		die("outfile Error", 1, (int []){pipe_fd[0], pipe_fd[1], outfile});
	cmd2 = ft_split(argv[3], ' ');
	if (!cmd2)
		die("malloc failed", 1, (int []){pipe_fd[0], pipe_fd[1], outfile});
	full_path = find_path(paths, cmd2[0]);
	if (!full_path)
		die("no found path", 127, (int []){pipe_fd[0], pipe_fd[1], outfile});
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	execve(full_path, cmd2, envp);
	die("execve failed", 126, (int []){pipe_fd[0], pipe_fd[1], outfile});
}

void	parent(char **argv, char **paths, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipe_fd) == -1)
		die("pipe failed", 1, NULL);
	pid1 = fork();
	if (pid1 == -1)
		die("fork failed", 1, NULL);
	if (pid1 == 0)
		child1(argv, pipe_fd, paths, envp);
	pid2 = fork();
	if (pid2 == -1)
		die("fork failed", 1, NULL);
	if (pid2 == 0)
		child2(argv, pipe_fd, paths, envp);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	char	**paths;

	if (argc == 5)
	{
		paths = split_paths(envp);
		if (!paths)
			die("path not found", 1, NULL);
		parent(argv, paths, envp);
		free_paths(paths);
	}
	return (0);
}
