/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:05:28 by msoria-j          #+#    #+#             */
/*   Updated: 2023/04/10 10:26:31 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex_bonus.h"

void	exec_cmd(t_paths *p, char *cmd)
{
	char	*tmp_path;
	int		i;

	if (p->envp == NULL)
		exit_no_envp(p->argv);
	if (access(p->args[0], F_OK | X_OK) == 0)
		if (execve(p->args[0], p->args, p->envp) == -1)
			exit_error(p, "Error on execve args[0]", errno);
	i = -1;
	while (p->paths[++i])
	{
		tmp_path = ft_strjoin(p->paths[i], "/");
		p->cmd = ft_strjoin(tmp_path, p->args[0]);
		free(tmp_path);
		if (access(p->cmd, F_OK | X_OK) == 0)
			if (execve(p->cmd, p->args, p->envp) == -1)
				exit_error(p, "Error on execve p->cmd", errno);
		free(p->cmd);
		p->cmd = NULL;
	}
	exit_no_cmd(p, cmd);
}

void	exec_child(t_descriptors d, t_paths *p, int index)
{
	if (pipe(d.pipe_fd) == -1)
		exit(EXIT_FAILURE);
	d.fork_id = fork();
	if (d.fork_id == -1)
		exit(EXIT_FAILURE);
	if (d.fork_id == 0)
	{
		p->args = ft_split_args(p->argv[index]);
		close(d.pipe_fd[0]);
		dup2(d.pipe_fd[1], STDOUT_FILENO);
		close(d.pipe_fd[1]);
		exec_cmd(p, p->args[0]);
	}
	else
	{
		close(d.pipe_fd[1]);
		dup2(d.pipe_fd[0], STDIN_FILENO);
		close(d.pipe_fd[0]);
		waitpid(d.fork_id, NULL, WNOHANG);
	}
}

void	exec_parent(t_descriptors d, t_paths *p, int index)
{
	p->args = ft_split_args(p->argv[index]);
	d.file = open_file(p, p->mode);
	dup2(d.file, STDOUT_FILENO);
	close(d.file);
	exec_cmd(p, p->args[0]);
}

/* Every time a fork is done, the execution has to finish, */
/* either via execve or via exit()*/
void	exec_here_doc(char *buf)
{
	t_descriptors	d;

	if (pipe(d.pipe_fd) == -1)
		exit(EXIT_FAILURE);
	d.fork_id = fork();
	if (d.fork_id == -1)
		exit(EXIT_FAILURE);
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
