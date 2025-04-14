/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:38:15 by roversch          #+#    #+#             */
/*   Updated: 2025/04/14 19:23:54 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>

void	die(t_px *px, t_fd *fd, const char *msg, int exit_code)
{
	if (fd)
	{
		close(fd->in);
		close(fd->out);
		close(fd->pipe[0]);
		close(fd->pipe[1]);
	}
	free_array(px->paths);
	perror(msg);
	exit(exit_code);
}

void	child(t_px *px, t_fd *fd)
{
	char	*full_path;

	px->cmd = ft_split(px->argv[px->i], ' ');
	if (!px->cmd)
		die(px, fd, "malloc error", 1);
	full_path = find_path(px->paths, px->cmd[0]);
	if (!full_path)
	{
		free_array(px->cmd);
		die(px, fd, "path error", 127);
	}
	dup2(fd->in, STDIN_FILENO);
	close(fd->in);
	dup2(fd->out, STDOUT_FILENO);
	close(fd->out);
	execve(full_path, px->cmd, px->envp);
	free(full_path);
	free_array(px->cmd);
	die(px, fd, "execve error", 126);
}

void	parent(t_px *px, t_fd *fd)
{
	pid_t	pid;

	while (px->i < px->argc - 1)
	{
		if (pipe(fd->pipe) == -1)
			die(px, fd, "pipe error", 1);
		pid = fork();
		if (pid == -1)
			die(px, fd, "fork error", 1);
		if (pid == 0)
		{
			close(fd->pipe[0]);
			if (px->i < px->argc - 2)
				fd->out = fd->pipe[1];
			child(px, fd);
		}
		close(fd->pipe[1]);
		if (px->i != 2)
			close(fd->in);
		fd->in = fd->pipe[0];
		waitpid(pid, NULL, 0);
		px->i++;
	}
}

int	build_structs(int argc, char **argv, char **envp)
{
	t_px		px;
	t_fd		fd;

	if (argc < 5)
	{
		perror("input err");
		return (1);
	}
	px.i = 2;
	px.argc = argc;
	px.argv = argv;
	px.envp = envp;
	px.paths = split_paths(envp);
	if (!px.paths)
		die(&px, NULL, "path error", 1);
	fd.in = open(argv[1], O_RDONLY);
	if (fd.in == -1)
		die(&px, &fd, "infile error", 1);
	fd.out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd.out == -1)
		die(&px, &fd, "outfile error", 1);
	parent(&px, &fd);
	//close?
	free_array(px.paths);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	return (build_structs(argc, argv, envp));
}
