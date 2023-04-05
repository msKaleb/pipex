/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:55:08 by msoria-j          #+#    #+#             */
/*   Updated: 2023/04/05 16:12:27 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

void	exec_hd_child(t_descriptors d, t_paths *p)
{
	p->args = ft_split_args(p->argv[3]);
	close(d.pipe_fd[0]);
	d.file = open("tmp", O_RDONLY);
	if (d.file == -1)
		exit_no_infile(p->argv);
	// ft_fprintf(2, "arg: %s\n", p->argv[3]);
	dup2(d.file, STDIN_FILENO);
	close(d.file);
	unlink("tmp");
	dup2(d.pipe_fd[1], STDOUT_FILENO);
	close(d.pipe_fd[1]);
	exec_cmd(p, p->args[0]);
}
void	exec_hd_parent(t_descriptors d, t_paths *p)
{
	// perror("puta mierda");
	close(d.pipe_fd[1]);
	p->args = ft_split_args(p->argv[4]);
	dup2(d.pipe_fd[0], STDIN_FILENO);
	close(d.pipe_fd[0]);
	d.file = open(p->argv[5], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (d.file == -1)
		exit_error(p, "Error on parent process", errno);
	dup2(d.file, STDOUT_FILENO);
	close(d.file);
	// ft_fprintf(2, "arg: %s\n", p->args[0]);
	exec_cmd(p, p->args[0]);
}

void	exec_here_doc(t_paths *p, char *buf)
{
	t_descriptors	d;

	(void) p;
	pipe(d.pipe_fd);
	d.fork_id = fork();
	waitpid(d.fork_id, NULL, WNOHANG);
	// ft_fprintf(2, "%s", buf);

	if (d.fork_id == 0)
		ft_fprintf(d.pipe_fd[1], "%s", buf);
	else
	{
		close(d.pipe_fd[1]);
		dup2(d.pipe_fd[0], 0);
		close(d.pipe_fd[0]);
		d.file = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(d.file, STDOUT_FILENO);
		close(d.file);
		p->args = ft_split_args(p->argv[3]);
		exec_cmd(p, p->args[0]);
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
	// ft_fprintf(2, "%s\n", v.buf);
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

int	main(int argc, char **argv, char **envp)
{
	t_descriptors	d;
	t_paths			p;
	t_vars			v;
	
	v.i = 0;
	while (ft_strnstr(envp[v.i], "PATH", 4) == 0)
		v.i++;
	p.paths = ft_split(envp[v.i] + 5, ':');
	p.argv = argv;
	p.envp = envp;
	check_argc(argc);
	if (ft_strnstr(argv[1], "here_doc", 8))
		here_doc(&p);
/* 	d.file = open("tmp", O_RDONLY);
	if (d.file == -1)
		exit_no_infile(p.argv); */
	pipe(d.pipe_fd);
	d.fork_id = fork();
	waitpid(d.fork_id, NULL, WNOHANG);
	if (d.fork_id == 0)
		exec_hd_child(d, &p);
	else
		exec_hd_parent(d, &p);
	/* waitpid(d.fork_id, &v.i, WNOHANG);
	p.input = p.argv[1];
	if (d.fork_id == 0)
		exec_child(d, &p, 3);
	else
		exec_parent(d, &p, 4);
	free_structs(&p, FREE_ALL); */
	return (EXIT_SUCCESS);
}
