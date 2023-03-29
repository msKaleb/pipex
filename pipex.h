/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:37:32 by msoria-j          #+#    #+#             */
/*   Updated: 2023/03/29 17:55:38 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define FREE_ARGS 1
# define FREE_PATHS 2
# define FREE_CMD 4
# define FREE_ALL 7

# include "./ft_printf/ft_printf.h"
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

void	exit_error(t_paths *p, char *str);
void	free_structs(t_paths *p, int flag);
void	exec_cmd(t_paths *p);
void	exec_child(t_descriptors d, t_paths *p);
void	exec_parent(t_descriptors d, t_paths *p);
char	**ft_split_args(char *str);
int		ft_wordcount(char *str);
int		get_length(char *str);

#endif