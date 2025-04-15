/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:38:15 by roversch          #+#    #+#             */
/*   Updated: 2025/04/15 14:14:15 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>

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

	px->i = 2;
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

// void	here_doc(t_px *px, t_fd *fd)
// {
// 	pid_t	hid;
// 	char	*line;

// 	px->i = 3;	
// 	if (pipe(fd->pipe) == -1)
// 			die(px, fd, "pipe error", 1);
// 	hid = fork();
// 	if (hid == -1)
// 		die(px, fd, "fork error", 1);
// 	if (hid == 0)
// 	{
// 		close(fd->pipe[0]);
// 		while (get_next_line(&line))
// 		{
// 			if (ft_strncmp(line, px->argv[2], ft_strlen(px->argv[2])) == 0)
// 				exit(EXIT_SUCCESS);
// 			write(fd->pipe[1], line, ft_strlen(line));
// 		}
// 	}
// 	close(fd->pipe[1]);
// 	waitpid(hid, NULL, 0);
// }

void	build_structs(t_px *px, t_fd *fd, int argc, char **argv)
{
	px->argc = argc;
	px->argv = argv;
	px->paths = split_paths(px->envp);
	if (!px->paths)
		die(px, NULL, "path error", 1);
	fd->in = open(argv[1], O_RDONLY);
	if (fd->in == -1)
		die(px, fd, "infile error", 1);
	fd->out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd->out == -1)
		die(px, fd, "outfile error", 1);
}
int	pipex(int argc, char **argv, char **envp)
{
	t_px		px;
	t_fd		fd;

	if (argc < 5 || (!ft_strncmp(argv[1], "here_doc", 9) && argc < 6))
		return (perror("input error"), 1);
	px.envp = envp;
	build_structs(&px, &fd, argc, argv);

	// if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	// 	here_doc(&px, &fd);
	// else
		parent(&px, &fd);
	//close?
	free_array(px.paths);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	return (pipex(argc, argv, envp));
}
