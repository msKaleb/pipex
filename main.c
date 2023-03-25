/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:20:08 by msoria-j          #+#    #+#             */
/*   Updated: 2023/03/25 20:21:47 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

void	nl(void)
{
	ft_printf("\n");
}

int	main(int argc, char **argv, char **envp)
{
	t_paths	p;
	int		pipe_fd[2];
	int		file;
	int		fork_id;
	int		i;

	if (argc < 5)
		exit (0);
	i = 0;
	while (envp[i++])
		if (ft_strncmp(ft_substr(envp[i], 0, 5), "PATH=", 5) == 0)
			break ;
	p.path_line = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	p.paths = ft_split(p.path_line, ':');
	p.args = ft_split(argv[2], ' ');
	/* comprobar argumentos */
	// i = -1;
	// while (p.args[i++])
	// 	ft_printf("arg: %s\n", p.args[i]);
	// exit(0);
	file = open(argv[1], O_RDONLY);
	pipe(pipe_fd);
	fork_id = fork();
	wait(NULL);
	if (fork_id == 0)
	{
		close(pipe_fd[0]);
		dup2(file, STDIN_FILENO);
		close(file);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		i = -1;
		while (p.paths[++i])
		{
			p.cmd = ft_strjoin(ft_strjoin(p.paths[i], "/"), p.args[0]);
			execve(p.cmd, p.args, p.paths);
			free(p.cmd);
		}
	}
	else
	{
		close(pipe_fd[1]);
		i = -1;
		while (p.args[++i])
			free(p.args[i]);
		free(p.args);
		p.args = ft_split(argv[3], ' ');
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(file, STDOUT_FILENO);
		close(file);
		i = -1;
		while (p.paths[++i])
		{
			p.cmd = ft_strjoin(ft_strjoin(p.paths[i], "/"), p.args[0]);
			execve(p.cmd, p.args, p.paths);
			free(p.cmd);
		}
	}
	return (1);
}
