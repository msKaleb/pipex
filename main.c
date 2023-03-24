/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:20:08 by msoria-j          #+#    #+#             */
/*   Updated: 2023/03/24 15:11:17 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf/ft_printf.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

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
	int		infile;
	int		id;
	
	infile = open(argv[1], O_RDONLY);
	pipe(pipe_fd);
	id = fork();
	
	if (argc < 2)
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
	
	/* recorro el bucle de paths buscando el adecuado,
	si no lo encuentra, libera cmd */
	if (id == 0){
		dup2(infile, STDIN_FILENO);
		close(infile);
		j = -1;
		ft_printf("child: %d\n", id);
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
		// ft_printf("parent: 5d\n", id);
		
	}
	return (1);
}