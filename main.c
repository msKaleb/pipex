/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:20:08 by msoria-j          #+#    #+#             */
/*   Updated: 2023/03/25 19:24:31 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf/ft_printf.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

void	nl(void)
{
	ft_printf("\n");
}

int	main(int argc, char **argv, char **envp)
{
	/* crear struct */
	char	*path_line;
	char	**path_array;
	char	**args;
	char	*cmd;
	
	int		i, j;
	int		pipe_fd[2];
	int		file;
	int		id;
	
	file = open(argv[1], O_RDONLY);
	pipe(pipe_fd);
	id = fork();
	
	if (argc < 5)
		exit (0);
	i = 0;
	/* busco la línea con las rutas (paths) */
	while (envp[i++])
		if (ft_strncmp(ft_substr(envp[i], 0, 5), "PATH=", 5) == 0)
			break ;
	/* saco la string con todos los paths */
	path_line = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	/* creo un array de strings con los paths */
	path_array = ft_split(path_line, ':');
	/* creo un array de strings con los argumentos del segundo comando */
	args = ft_split(argv[2], ' ');
	
	/* comprobar argumentos */
	// j = -1;
	// while (args[j++])
	// 	ft_printf("arg: %s\n", args[j]);
	
	while (wait(NULL) != -1 || errno != ECHILD); // para esperar a que termine el proceso hijo, mirar el retorno de wait
	/* recorro el bucle de paths buscando el adecuado,
	si no lo encuentra, libera cmd */
	if (id == 0)
	{
		close(pipe_fd[0]);
		dup2(file, STDIN_FILENO);
		close(file);
		
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);

		j = -1;
		// ft_printf("child: %d\n", id);
		while (path_array[++j])
		{
			//ft_printf("path: %s\n", path_array[j]);
			cmd = ft_strjoin(ft_strjoin(path_array[j], "/"), args[0]);
			// ft_printf("command: %s\n", cmd);
			execve(cmd, args, path_array);
			// perror(0); // for debugging
			free(cmd);
		}
	}
	else
	{
		// ft_printf("parent: %d\n", id);
		close(pipe_fd[1]);
		j = -1;
		while (args[++j])
			free(args[j]);
		free(args);
		args = ft_split(argv[3], ' ');

		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);

		// archivo para output del segundo comando
		// ft_printf("output file: %s\n", argv[4]);
		file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(file, STDOUT_FILENO);
		close(file);

		j = -1;
		while (path_array[++j])
		{
			cmd = ft_strjoin(ft_strjoin(path_array[j], "/"), args[0]);
			execve(cmd, args, path_array);
			free(cmd);
		}
	}
	return (1);
}