/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:26:36 by msoria-j          #+#    #+#             */
/*   Updated: 2023/03/30 17:52:12 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_wordcount(char *str)
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

static int	get_length(char *str)
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
	if (str[len] == 34)
	{
		len++;
		while (str[len] != 34 && str[len])
			len++;
		len++;
		return (len);
	}
	while (str[len] != 32 && str[len])
		len++;
	return (len);
}

static char *ft_trim_quotes(char *str)
{
	char 	*tmp;
	int		check;

	check = ft_strlen(ft_strchr(str, 34)) - ft_strlen(ft_strchr(str, 39));
	ft_printf("len: %d\n", check);
	if (check == -1)
	{
		//puta mierda
	}
	if (ft_strchr(str, 34) || check == 1)
	{
		tmp = ft_strtrim(str, "\"");
		free(str);
		return (tmp);
	}
	if (ft_strchr(str, 39))
	{
		tmp = ft_strtrim(str, "'");
		free(str);
		return (tmp);
	}
	return (str);
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
			args[i] = ft_trim_quotes(args[i]);
			i++;
			str += len;
		}
	}
	args[i] = NULL;
	return (args);
}
