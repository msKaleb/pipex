/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:20:08 by msoria-j          #+#    #+#             */
/*   Updated: 2023/03/11 18:15:02 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf/ft_printf.h"

int	main(int ac, char **av)
{
	char	*env_args[] = { NULL };
	char	*command;
	int		size = ft_strlen("/usr/bin/") + ft_strlen(av[1]) + 1;
	
	command = ft_calloc(1, size);
	av[ac] = NULL;
	if (ac == 1)
		exit (0);
	execve(av[1], av, env_args);
	ft_strlcat(command, "/usr/bin/", size);
	ft_strlcat(command, av[1], size);
	command[size] = 0;
	ft_printf("%s\n", command);
	ft_printf("av: %d\n", execve(command, av, env_args));
	free(command);
	return (1);
}