/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:59:36 by msoria-j          #+#    #+#             */
/*   Updated: 2023/04/07 11:18:22 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_error(t_paths *p, char *str, int err_code)
{
	if (p)
		free_structs(p, FREE_ALL);
	perror(str);
	exit(err_code);
}

/* TODO: check and compare with bash output */
void	exit_no_infile(char **argv)
{
	int		fd;

	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error");
		exit(errno);
	}
	write(fd, "0\n", 2);
	ft_fprintf(2, "%s: line 1: %s: ", ft_strchr(argv[0], '/') + 1, argv[1]);
	perror("");
	close(fd);
	exit(0);
}

/* TODO: check and compare with bash output */
void	exit_no_envp(char **argv)
{
	int		fd;

	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error");
		exit(errno);
	}
	ft_fprintf(fd, "1\n");
	close(fd);
	exit(EAGAIN);
}

/* TODO: check and compare with bash output */
void	exit_no_cmd(t_paths *p, char *err)
{
	ft_fprintf(2, "%s: line 1: %s: ", ft_strchr(p->argv[0], '/') + 1, err);
	ft_fprintf(2, "command not found\n");
	free_structs(p, FREE_ALL);
	exit(ECMD_NOT_FOUND);
}

/* Function to free alloc'd data */
void	free_structs(t_paths *p, int flag)
{
	int	i;

	if (flag & FREE_ARGS)
	{
		i = -1;
		while (p->args[++i])
			free(p->args[i]);
		free(p->args);
	}
	if (flag & FREE_PATHS)
	{
		i = -1;
		while (p->paths[++i])
			free(p->paths[i]);
		free(p->paths);
	}
	if (flag & FREE_CMD)
		free(p->cmd);
}
