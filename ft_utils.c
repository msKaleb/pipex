/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:59:36 by msoria-j          #+#    #+#             */
/*   Updated: 2023/03/29 14:00:11 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"
/* Function to free alloc'd data */
void	free_structs(t_paths *p, int flag)
{
	int	i;

	if (flag == FREE_ALL || flag == FREE_ARGS)
	{
		i = -1;
		while (p->args[++i])
			free(p->args[i]);
		free(p->args);
	}
	if (flag == FREE_ALL || flag == FREE_PATHS)
	{
		i = -1;
		while (p->paths[++i])
			free(p->paths[i]);
		free(p->paths);
	}
}