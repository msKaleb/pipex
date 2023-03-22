/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:20:08 by msoria-j          #+#    #+#             */
/*   Updated: 2023/03/22 21:04:39 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf/ft_printf.h"
#include <unistd.h>
#include <stdio.h>

void	nl(void)
{
	ft_printf("\n");
}

int	main(int argc, char **argv, char **envp)
{
	char	*path_line;
	char	**path_array;
	char	**args;
	char	*cmd;
	// char	*args[] = {"/usr/bin/ls", "-l", "-a", "-h", (char *)0};
	int		i, j;
	
	if (argc < 2)
		exit (0);
	/****** rellenar args con el contenido de argv ******/
	i = 0;
	while (envp[i++])
		if (ft_strncmp(ft_substr(envp[i], 0, 5), "PATH=", 5) == 0)
			break ;
	// saco la string con todos los paths
	path_line = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	// creo un array de strings con los paths
	path_array = ft_split(path_line, ':');
	// creo un array de strings con los argumentos del primer comando
	// (el número de argv cambiará a 2 con infile)
	args = ft_split(argv[1], ' ');
	
	// comprobar argumentos
/* 	j = -1;
	while (args[j++])
		ft_printf("arg: %s\n", args[j]); */
		
	j = -1;
	nl();
	while (path_array[++j])
	{
		//ft_printf("path: %s\n", path_array[j]);
		cmd = ft_strjoin(ft_strjoin(path_array[j], "/"), args[0]);
		// ft_printf("path: %s\n", cmd);
		execve(cmd, args, path_array);
		// perror(0); // for debugging
		free(cmd);
	}
	return (1);
}