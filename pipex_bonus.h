/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:37:32 by msoria-j          #+#    #+#             */
/*   Updated: 2023/04/02 14:52:24 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# define FREE_ARGS 1
# define FREE_PATHS 2
# define FREE_CMD 4
# define FREE_ALL 7

# define ECMD_NOT_FOUND 127

# include "./ft_fprintf/ft_fprintf.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>

typedef struct s_paths
{
	char	**paths;
	char	**args;
	char	**argv;
	char	**envp;
	char	*cmd;
}				t_paths;

typedef struct s_descriptors
{
	int		pipe_fd[2];
	int		file;
	int		fork_id;
}				t_descriptors;

void	exit_error(t_paths *p, char *str, int err_code);
void	free_structs(t_paths *p, int flag);
void	exec_cmd(t_paths *p, char *cmd);
void	exec_child(t_descriptors d, t_paths *p);
void	exec_parent(t_descriptors d, t_paths *p);
char	**ft_split_args(char *str);
void	exit_no_infile(char **argv);
void	exit_no_cmd(t_paths *p, char *err);
void	exit_no_envp(char **argv);

#endif