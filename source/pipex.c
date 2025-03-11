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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

void	child(char **argv, int *pipe_fd)
{
	int	infile;
	char *cmd1[] = {"/bin/cat", argv[1], NULL};

	close(pipe_fd[0]);
	infile = open(argv[1], O_RDONLY);
	dup2(infile, STDIN_FILENO); 
	close(infile);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[1]);
	execve(cmd1[0], cmd1, NULL);
}

void	parent(char **argv, int *pipe_fd)
{
	int	outfile;
	char *cmd2[] = {"/usr/bin/wc", NULL};

	wait(NULL);
	close(pipe_fd[1]);
	outfile = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
	execve(cmd2[0], cmd2, NULL);
}

int	main(int argc, char **argv)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (argc == 3)
	{	
		pipe(pipe_fd);
		pid = fork();
		if (pid == 0)
			child(argv, pipe_fd);
		else
		parent(argv, pipe_fd);
	}
	return (0);
}
