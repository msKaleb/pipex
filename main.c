/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:20:08 by msoria-j          #+#    #+#             */
/*   Updated: 2023/03/29 14:26:43 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

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



void	exec_cmd(t_paths *p)
{
	int	i;

	i = -1;
	while (p->paths[++i])
	{
		p->cmd = ft_strjoin(ft_strjoin(p->paths[i], "/"), p->args[0]);
		if (access(p->cmd, F_OK) == 0)
		{
			if (execve(p->cmd, p->args, p->envp) == -1)
				exit(errno);
			perror("execve"); // mirar
		}
		free(p->cmd);
	}
}

static void	exec_child(t_descriptors d, t_paths *p)
{
	close(d.pipe_fd[0]);
	dup2(d.file, STDIN_FILENO);
	close(d.file);
	dup2(d.pipe_fd[1], STDOUT_FILENO);
	close(d.pipe_fd[1]);
	exec_cmd(p);
}

static void	exec_parent(t_descriptors d, t_paths *p)
{
	close(d.pipe_fd[1]);
	free_structs(p, FREE_ARGS);
	p->args = ft_split_args(p->argv[3]);
	dup2(d.pipe_fd[0], STDIN_FILENO);
	close(d.pipe_fd[0]);
	d.file = open(p->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (d.file == -1)
		error_open(p);
	dup2(d.file, STDOUT_FILENO);
	close(d.file);
	exec_cmd(p);
}

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

int	main(int argc, char **argv, char **envp)
{
	t_descriptors	d;
	t_paths			p;
	int				i;

	errno = 0;
	check_argc(argc);
	d.file = open(argv[1], O_RDONLY);
	p.args = ft_split_args(argv[2]);
	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	p.paths = ft_split(envp[i] + 5, ':');
	p.argv = argv;
	p.envp = envp;
	pipe(d.pipe_fd);
	d.fork_id = fork();
	// wait(NULL);
	waitpid(d.fork_id, NULL, WNOHANG);
	if (d.fork_id == 0)
		exec_child(d, &p);
	else
		exec_parent(d, &p);
	close(d.file);
	return (EXIT_SUCCESS);
}
