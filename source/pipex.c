/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:27:58 by roversch          #+#    #+#             */
/*   Updated: 2025/03/17 17:01:51 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>


void	free_paths(char **paths)
{
	int	i;

	if (!paths)
		return;
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

char	**split_paths(char **envp)
{
	char	**paths;
	char	*tmp;
	int	i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(tmp, "/");
		free(tmp);
		i++;
	}
	return (paths);
}

char	*find_path(char **paths, char *cmd)
{
	int		i;
	char	*found_path;
	char	*tmp;

	i = 0;
	printf("[findpath]\n");
	while (paths[i])
	{
		printf("%s\n", paths[i]);
		i++;
	}
	i = 0;
	printf("cmd:%s\n", cmd);
	while (paths[i])
	{
		tmp = paths[i];
		found_path = ft_strjoin(tmp, cmd);
		printf("%s\n", found_path);
		if (access(found_path, F_OK) == 0)
		{
			printf("foundpath\n");
			return (found_path);
		}
		free(found_path);
		i++;
	}
	printf("\n");
	return (0);
}

void	child(char **argv, int *pipe_fd, char **paths)
{
	int	infile;
	printf("[child]\n");
	char *cmd1[] = {find_path(paths, argv[2]), NULL};

	close(pipe_fd[0]);
	infile = open(argv[1], O_RDONLY);
	dup2(infile, STDIN_FILENO); 
	close(infile);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	execve(cmd1[0], cmd1, NULL);
}

void	parent(char **argv, int *pipe_fd, char **paths)
{
	int	outfile;
	printf("[parent]\n");
	char *cmd2[] = {find_path(paths, argv[3]), NULL};

	wait(NULL);
	close(pipe_fd[1]);
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	execve(cmd2[0], cmd2, NULL);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid;
	char	**paths;
	int	i;
	
	paths = split_paths(envp);
	i = 0;
	printf("[baseline]\n");
	while (paths[i])
	{
		printf("%s\n", paths[i]);
		i++;
	}
	printf("\n");
	if (argc == 5)
	{	
		pipe(pipe_fd); //check for succes?
		pid = fork();
		if (pid == -1)
			return (printf("error\n"), 1);
		if (pid == 0)
			child(argv, pipe_fd, paths);
		else
		parent(argv, pipe_fd, paths);
	}
	free_paths(paths);
	return (0);
}

// ./pipex infile.txt cat wc outfile.txt
