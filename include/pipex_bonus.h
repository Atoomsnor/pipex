/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:28:58 by roversch          #+#    #+#             */
/*   Updated: 2025/04/15 14:04:57 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include "../libft/libft.h"

typedef struct s_fd
{
	int	in;
	int	out;
	int	pipe[2];
}	t_fd;

typedef struct s_px
{
	int		i;
	int		argc;
	char	**argv;
	char	**paths;
	char	**envp;
	char	**cmd;
}	t_px;

/* Error Handling */
void	die(t_px *px, t_fd *fd, const char *msg, int exit_code);

/* Process Management */
void	here_doc(t_px *px, t_fd *fd);
void	parent(t_px *px, t_fd *fd);
void	child(t_px *px, t_fd *fd);

/* Path Handling */
char	**split_paths(char **envp);
char	*find_path(char **paths, char *cmd);
void	free_array(char **array);

/* Main Function */
void	build_structs(t_px *px, t_fd *fd, int argc, char **argv);
int		pipex(int argc, char **argv, char **envp);
int		main(int argc, char **argv, char **envp);

#endif