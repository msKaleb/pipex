/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:26:36 by msoria-j          #+#    #+#             */
/*   Updated: 2023/03/28 12:35:07 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_wordcount(char *str)
{
	int		isstr;
	int		strnumber;
	int		i;

	i = 0;
	isstr = 0;
	strnumber = 0;
	while (str[i])
	{
		if (str[i] == 39)
		{
			i++;
			while (str[i] != 39)
				i++;
		}
		if (str[i] != 32 && isstr == 0)
		{
			strnumber++;
			isstr = 1;
		}
		if (str[i] == 32)
			isstr = 0;
		i++;
	}
	return (strnumber);
}

int	get_length(char *str)
{
	int	len;

	len = 0;
	if (str[len] == 39)
	{
		len++;
		while (str[len] != 39 && str[len])
			len++;
		len++;
		return (len);
	}
	while (str[len] != 32 && str[len])
		len++;
	return (len);
}

char	**ft_split_args(char *str)
{
	char	**args;
	int		i;
	int		len;

	args = malloc((ft_wordcount(str) + 1) * sizeof(args));
	if (!args)
		return (NULL);
	i = 0;
	while (*str)
	{
		while (*str == 32)
			str++;
		if (*str)
		{
			len = get_length(str);
			args[i] = ft_substr(str, 0, len);
			i++;
			str += len;
		}
	}
	args[i] = NULL;
	return (args);
}
