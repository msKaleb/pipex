/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:55:08 by msoria-j          #+#    #+#             */
/*   Updated: 2023/04/06 16:13:09 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

void	exec_here_doc(t_paths *p, char *buf)
{
	t_descriptors	d;

	ft_strlcpy(p->input, "tmp", 4);
	d.file = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_fprintf(d.file, "%s", buf);
	close(d.file);
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
	exec_here_doc(p, v.buf);
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

int	main(int argc, char **argv, char **envp)
{
	t_descriptors	d;
	t_paths			p;
	int				arg;
	
	arg = 2;
	check_argc(argc);
	p = init_pvar(argc, argv, envp);
	if (ft_strnstr(argv[1], "here_doc", 8))
	{
		here_doc(&p);
		arg = 3;
	}
	pipe(d.pipe_fd);
	d.fork_id = fork();
	if (d.fork_id == 0)
		exec_child(d, &p, arg);
	else
		exec_parent(d, &p, arg + 1);
	free_structs(&p, FREE_ALL);
	ft_fprintf(2, "%d\n", arg);
	return (EXIT_SUCCESS);
}
