/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:37:32 by msoria-j          #+#    #+#             */
/*   Updated: 2023/03/28 12:35:46 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
	char	*path_line;
	char	*cmd;
}				t_paths;

typedef struct s_descriptors
{
	int		pipe_fd[2];
	int		file;
	int		fork_id;
}				t_descriptors;

char	**ft_split_args(char *str);
int		ft_wordcount(char *str);
int		get_length(char *str);

#endif