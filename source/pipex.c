#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

void free_paths(char **paths)
{
	int	i;

	if (!paths)
		return;
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

char **split_paths(char **envp)
{
	char	**paths;
	char	*tmp;
	int		i;

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

char *find_path(char **paths, char *cmd)
{
	char	*found_path;
	char	*tmp;
	int		i;

	i = 0;
	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (paths[i])
	{
		tmp = paths[i];
		found_path = ft_strjoin(tmp, cmd);
		if (access(found_path, F_OK) == 0)
			return (found_path);
		free(found_path);
		i++;
	}
	printf("\n");
	return (NULL);
}

void child1(char **argv, int *pipe_fd, char **paths, char **envp)
{
	int		infile;
	char	*full_path;
	char	**cmd1;

	infile = open(argv[1], O_RDONLY);
	dup2(infile, STDIN_FILENO);
	close(infile);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	close(pipe_fd[0]);

	cmd1 = ft_split(argv[2], ' ');
	full_path = find_path(paths, cmd1[0]);
	execve(full_path, cmd1, envp);
	exit(1);
}

void child2(char **argv, int *pipe_fd, char **paths, char **envp)
{
	int		outfile;
	char	*full_path;
	char	**cmd2;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	close(pipe_fd[1]);

	cmd2 = ft_split(argv[3], ' ');
	full_path = find_path(paths, cmd2[0]);
	execve(full_path, cmd2, envp);
	exit(2);
}

void	parent(char **argv, char **paths, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	pipe(pipe_fd);

	pid1 = fork();
	if (pid1 == 0)
		child1(argv, pipe_fd, paths, envp);

	pid2 = fork();
	if (pid2 == 0)
		child2(argv, pipe_fd, paths, envp);

	close(pipe_fd[0]);
	close(pipe_fd[1]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int main(int argc, char **argv, char **envp)
{
	char	**paths;

	if (argc == 5)
	{
		paths = split_paths(envp);
		if (!paths)
		{
			fprintf(stderr, "Failed to split paths\n");
			return (1);
		}
		parent(argv, paths, envp);
		free_paths(paths);
	}
	return (0);
}
