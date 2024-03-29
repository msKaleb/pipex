/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:20:08 by msoria-j          #+#    #+#             */
/*   Updated: 2023/03/31 13:41:22 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

/* Check arguments array */
/* static void	check_args_value(t_paths p)
{
	int	i;

	i = -1;
	while (p.args[i++])
		ft_printf("arg: %s\n", p.args[i]);
	exit(0);
} */

/* Check paths array */
/* static void	check_paths_value(t_paths p)
{
	int	i;

	i = -1;
	while (p.paths[i++])
		ft_printf("path: %s\n", p.paths[i]);
	exit(0);
} */

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
	d.file = open(argv[1], O_RDONLY);
	if (d.file == -1)
		exit_no_infile(argv);
	p.args = ft_split_args(argv[2]);
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
	close(d.file);
	free_structs(&p, FREE_ALL);
	return (EXIT_SUCCESS);
}
