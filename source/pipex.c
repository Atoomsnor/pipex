/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:27:58 by roversch          #+#    #+#             */
/*   Updated: 2025/03/12 15:59:15 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <fcntl.h>
// #include <unistd.h>

// int main()
// {
// 	int fd;

// 	fd = open("example.txt", O_WRONLY);
// 	dup2(fd, STDOUT_FILENO);
// 	close(fd);
// 	printf("eat ass");
// 	return (0);
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <sys/types.h>
// #include <sys/wait.h>

// int main()
// {
// 	int pipe_fd[2];
// 	pid_t pid;
// 	char buffer[12];
// 	int	infile;
// 	int	outfile;

// 	pipe(pipe_fd);
// 	pid = fork();

// 	if (pid == 0) // child is 0
// 	{
// 		close(pipe_fd[0]); // close the read end of the pipe
// 		infile = open("infile.txt", O_RDONLY);
// 		read(infile, buffer, 12);
// 		write(pipe_fd[1], buffer, 12);
// 		close(infile);
// 		close(pipe_fd[1]); // close the write end of the pipe
// 		exit(EXIT_SUCCESS);
// 	}
// 	else
// 	{
// 		close(pipe_fd[1]); // close the write end of the pipe
// 		wait(NULL);
// 		outfile = open("outfile.txt", O_WRONLY);
// 		read(pipe_fd[0], buffer, 12);
// 		write(outfile, buffer, 12);
// 		close(outfile);
// 		close(pipe_fd[0]); // close the read end of the pipe
// 		exit(EXIT_SUCCESS);
// 	}
// }

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

void	child(char **argv, int *pipe_fd, char **envp)
{
	int	infile;
	char *cmd1[] = {argv[2], NULL};

	close(pipe_fd[0]);
	infile = open(argv[1], O_RDONLY);
	dup2(infile, STDIN_FILENO); 
	close(infile);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	execve(cmd1[0], cmd1, envp);
}

void	parent(char **argv, int *pipe_fd, char **envp)
{
	int	outfile;
	char *cmd2[] = {argv[3], NULL};

	wait(NULL);
	close(pipe_fd[1]);
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	execve(cmd2[0], cmd2, envp);
}

char	*find_path(char **envp)
{
	int	i;
	int	j;
	char	**path;

	i = 0;
	j = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	path = ft_split(envp[i] + 5, ':');
	printf("%s\n", envp[i]);
	while (path)
	{
		printf("%s\n", path[i]);
		i++;
	}


	// strnstr to look for "PATH" PATH=/home/roversch/bin:/home/roversch/bin:--etc 
	// then strdup from path onwards
	// then ft_split at the : to make chunks, 2d array them?
	// after the last thing like /bin put the cmd1 like cat. and check path.
	// make cat into /bin/cat, wc into /usr/bin/wc, etc ft_split and look for / ?
	return (0);
}


int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid;

	find_path(envp);
	return (0);
	
	
	if (argc == 5)
	{	
		pipe(pipe_fd); //check for succes?
		pid = fork();
		if (pid == -1)
			return (printf("error\n"), 1);
		if (pid == 0)
			child(argv, pipe_fd, envp);
		else
		parent(argv, pipe_fd, envp);
	}
	return (0);
}

// ./pipex infile.txt /bin/cat /usr/bin/wc outfile.txt
