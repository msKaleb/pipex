/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:55:08 by msoria-j          #+#    #+#             */
/*   Updated: 2023/04/02 15:17:11 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* Check the argument number */
static void	check_argc(int argc)
{
	if (argc > 5)
	{
		errno = E2BIG;
		perror("Error");
		exit(errno);
	}
	if (argc < 5)
	{
		errno = EINVAL;
		perror("Error");
		exit(errno);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_descriptors	d;
	t_paths			p;
	int				i;

	check_argc(argc);
	p.argv = argv;
	p.envp = envp;
	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	p.paths = ft_split(envp[i] + 5, ':');
	pipe(d.pipe_fd);
	d.fork_id = fork();
	waitpid(d.fork_id, &i, WNOHANG);
	if (d.fork_id == 0)
		exec_child(d, &p);
	else
		exec_parent(d, &p);
	free_structs(&p, FREE_ALL);
	return (EXIT_SUCCESS);
}
