/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:55:08 by msoria-j          #+#    #+#             */
/*   Updated: 2023/04/10 08:38:18 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

int	open_file(t_paths *p, int mode)
{
	int	fd;

	if (mode == 0)
	{
		fd = open(p->input, O_RDONLY);
		if (fd == -1)
			exit_no_infile(p);
	}
	if (mode == 1)
	{
		fd = open(p->argv[p->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			exit_error(p, "Error on parent process", errno);
	}
	if (mode == 2)
	{
		fd = open(p->argv[p->argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			exit_error(p, "Error on parent process", errno);
	}
	return (fd);
}

/* Check the argument number */
static void	check_argc(int argc)
{
	if (argc < 5)
	{
		errno = EINVAL;
		perror("Error");
		exit(errno);
	}
}

t_paths	init_pvar(int argc, char **argv, char **envp)
{
	t_paths	p;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	p.paths = ft_split(envp[i] + 5, ':');
	p.argv = argv;
	p.input = p.argv[1];
	p.envp = envp;
	p.argc = argc;
	p.mode = 1;
	return (p);
}

/* TODO: Check pipe and fork returns */
int	main(int argc, char **argv, char **envp)
{
	t_descriptors	d;
	t_paths			p;
	int				arg;

	arg = 1;
	check_argc(argc);
	p = init_pvar(argc, argv, envp);
	if (ft_strnstr(argv[1], "here_doc", 8))
	{
		here_doc(&p);
		p.mode = 2;
		arg = 2;
	}
	else
	{
		d.file = open_file(&p, 0);
		dup2(d.file, STDIN_FILENO);
		close(d.file);
	}
	while (++arg < p.argc - 2)
		exec_child(d, &p, arg);
	exec_parent(d, &p, arg);
	free_structs(&p, FREE_ALL);
	return (EXIT_SUCCESS);
}
