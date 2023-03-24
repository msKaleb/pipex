/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:20:08 by msoria-j          #+#    #+#             */
/*   Updated: 2023/03/24 15:45:42 by msoria-j         ###   ########.fr       */
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
	int		infile, outfile; // valdría solo con uno??
	int		id;
	
	infile = open(argv[1], O_RDONLY);
	pipe(pipe_fd);
	id = fork();
	
	if (argc < 3)
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
	/* creo un array de strings con los argumentos del primer comando
	(este método no funciona con ls, usar pipe()??) */
	/* argv[2] = ft_strjoin(argv[2], " <");
	argv[2] = ft_strjoin(argv[2], argv[1]); */
	// ft_printf("args: %s\n", argv[2]);
	args = ft_split(argv[2], ' ');
	
	/* comprobar argumentos */
/* 	j = -1;
	while (args[j++])
		ft_printf("arg: %s\n", args[j]); */
	
	while (wait(NULL) != -1 || errno != ECHILD); // para esperar a que termine el proceso hijo, mirar el retorno de wait
	/* recorro el bucle de paths buscando el adecuado,
	si no lo encuentra, libera cmd */
	if (id == 0){
		close(pipe_fd[0]);
		dup2(infile, STDIN_FILENO);
		close(infile);

		/* creo un archivo temporal para usarlo como input para el siguiente comando */
		outfile = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(outfile, STDOUT_FILENO);
		close(outfile);

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
	}else{
		// ft_printf("parent: %d\n", id);
		j = -1;
		while (args[++j])
			free(args[j]);
		free(args);
		args = ft_split(argv[3], ' ');

		// abrir temporal para usar como input
		infile = open("tmp", O_RDONLY);
		dup2(infile, STDIN_FILENO);
		close(infile);

		// archivo para output del segundo comando
		// ft_printf("output file: %s\n", argv[4]);
		outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(outfile, STDOUT_FILENO);
		close(outfile);

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