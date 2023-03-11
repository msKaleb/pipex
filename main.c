/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:20:08 by msoria-j          #+#    #+#             */
/*   Updated: 2023/03/10 16:35:45 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf/ft_printf.h"

int	main(int ac, char **av)
{
	char *env_args[] = { (char*)0 };

	if (ac == 1)
		exit (0);
	execve(av[1], av, env_args);
	ft_printf("av: %s\n", av[1]);
	return (1);
}