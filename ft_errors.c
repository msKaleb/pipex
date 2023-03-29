/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:33:59 by msoria-j          #+#    #+#             */
/*   Updated: 2023/03/29 14:14:38 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

void	error_open(t_paths *p)
{
	free_structs(p, FREE_ALL);
	perror("Error");
	exit(errno);
}
