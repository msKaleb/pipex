/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:55:08 by msoria-j          #+#    #+#             */
/*   Updated: 2023/04/07 17:28:01 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

/* Every time a fork is done, the execution has to finish, */
/* either via execve or via exit()*/
void	exec_here_doc(char *buf)
{
	t_descriptors	d;

	pipe(d.pipe_fd);
	d.fork_id = fork();
	if (d.fork_id == 0)
	{
		ft_fprintf(d.pipe_fd[1], "%s", buf);
		free(buf);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(d.pipe_fd[1]);
		dup2(d.pipe_fd[0], STDIN_FILENO);
		close(d.pipe_fd[0]);
		waitpid(d.fork_id, NULL, WNOHANG);
	}
}

void	here_doc(t_paths *p)
{
	t_vars	v;

	v.buf = ft_calloc(1, 1000 * sizeof(v.buf));
	v.i = -1;
	v.j = 0;
	while (++v.i < 1000)
	{
		read(STDIN_FILENO, v.buf, 1);
		if (*v.buf == '\n')
		{
			v.buf++;
			v.i++;
			v.j += v.i;
			if (ft_strnstr(v.buf - v.i, p->argv[2], ft_strlen(p->argv[2])))
				break ;
			else
				v.i = -1;
		}
		else
			v.buf++;
	}
	v.buf -= v.j;
	v.buf[v.j - v.i] = '\0';
	exec_here_doc(v.buf);
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
	return (p);
}

// exit_no_infile(p.argv); // pasar p (p.argv[p.argc - 1])
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
		arg = 2;
	}
	else
	{
		d.file = open(p.input, O_RDONLY);
		if (d.file == -1)
			exit_no_infile(&p);
		dup2(d.file, STDIN_FILENO);
		close(d.file);
	}
	while (++arg < p.argc - 2)
		exec_child(d, &p, arg);
	exec_parent(d, &p, arg);
	free_structs(&p, FREE_ALL);
	return (EXIT_SUCCESS);
}
