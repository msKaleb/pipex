/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:20:08 by msoria-j          #+#    #+#             */
/*   Updated: 2023/03/28 12:28:58 by msoria-j         ###   ########.fr       */
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

static void	exec_child(t_descriptors d, t_paths p)
{
	int	i;

	close(d.pipe_fd[0]);
	dup2(d.file, STDIN_FILENO);
	close(d.file);
	dup2(d.pipe_fd[1], STDOUT_FILENO);
	close(d.pipe_fd[1]);
	i = -1;
	while (p.paths[++i])
	{
		p.cmd = ft_strjoin(ft_strjoin(p.paths[i], "/"), p.args[0]);
		if (access(p.cmd, F_OK) == 0)
		{
			execve(p.cmd, p.args, p.paths);
			perror("execve");
		}
		free(p.cmd);
	}
}

static void	exec_parent(t_descriptors d, t_paths p, char **argv)
{
	int	i;

	close(d.pipe_fd[1]);
	i = -1;
	while (p.args[++i])
		free(p.args[i]);
	free(p.args);
	p.args = ft_split_args(argv[3]);
	dup2(d.pipe_fd[0], STDIN_FILENO);
	close(d.pipe_fd[0]);
	d.file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(d.file, STDOUT_FILENO);
	close(d.file);
	i = -1;
	while (p.paths[++i])
	{
		p.cmd = ft_strjoin(ft_strjoin(p.paths[i], "/"), p.args[0]);
		if (access(p.cmd, F_OK) == 0)
		{
			execve(p.cmd, p.args, p.paths);
			perror("execve");
		}
		free(p.cmd);
	}
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

int	main(int argc, char **argv, char **envp)
{
	t_descriptors	d;
	t_paths			p;
	int				i;

	check_argc(argc);
	p.args = ft_split_args(argv[2]);
	i = 0;
	while (envp[i++])
		if (ft_strncmp(ft_substr(envp[i], 0, 5), "PATH=", 5) == 0)
			break ;
	p.path_line = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	p.paths = ft_split(p.path_line, ':');
	d.file = open(argv[1], O_RDONLY);
	pipe(d.pipe_fd);
	d.fork_id = fork();
	wait(NULL);
	if (d.fork_id == 0)
		exec_child(d, p);
	else
		exec_parent(d, p, argv);
	return (EXIT_FAILURE);
}
