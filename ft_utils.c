/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:59:36 by msoria-j          #+#    #+#             */
/*   Updated: 2023/03/31 10:50:03 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_error(t_paths *p, char *str, int err_code)
{
	if (p)
		free_structs(p, FREE_ALL);
	perror(str);
	exit(err_code);
}

/* Function to free alloc'd data */
void	free_structs(t_paths *p, int flag)
{
	int	i;

	if (flag & FREE_ARGS)
	{
		i = -1;
		while (p->args[++i])
			free(p->args[i]);
		free(p->args);
	}
	if (flag & FREE_PATHS)
	{
		i = -1;
		while (p->paths[++i])
			free(p->paths[i]);
		free(p->paths);
	}
	if (flag & FREE_CMD)
		free(p->cmd);
}

void	exec_cmd(t_paths *p)
{
	char	*tmp_path;
	int		i;

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
	exit_error(p, "command not found", errno);
}

void	exec_child(t_descriptors d, t_paths *p)
{
	close(d.pipe_fd[0]);
	dup2(d.file, STDIN_FILENO);
	close(d.file);
	dup2(d.pipe_fd[1], STDOUT_FILENO);
	close(d.pipe_fd[1]);
	exec_cmd(p);
}

void	exec_parent(t_descriptors d, t_paths *p)
{
	close(d.pipe_fd[1]);
	free_structs(p, FREE_ARGS);
	p->args = ft_split_args(p->argv[3]);
	dup2(d.pipe_fd[0], STDIN_FILENO);
	close(d.pipe_fd[0]);
	d.file = open(p->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (d.file == -1)
		exit_error(p, "Error on parent", errno);
	dup2(d.file, STDOUT_FILENO);
	close(d.file);
	exec_cmd(p);
}
