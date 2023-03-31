/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:59:36 by msoria-j          #+#    #+#             */
/*   Updated: 2023/03/31 13:49:46 by msoria-j         ###   ########.fr       */
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
	close(fd);
	ft_printf("%s: %s: ",ft_strchr(argv[0], '/') + 1, argv[1]); //stderr
	perror("");
	exit(0);
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
