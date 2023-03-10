/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:59:36 by msoria-j          #+#    #+#             */
/*   Updated: 2022/12/18 19:33:32 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

int	print_char(char c)
{
	write (1, &c, 1);
	return (0);
}

int	print_str(char *s)
{
	if (!s)
		return (write(1, "(null)", 6) - 1);
	return (write(1, s, ft_strlen(s)) - 1);
}

int	print_hex(unsigned int p, char format)
{
	char	*s;
	int		ret;

	ret = 0;
	if (p == 0)
		return (write(1, "0", 1) - 1);
	s = change_base((unsigned long long)p, format);
	ret = write(1, s, ft_strlen(s));
	free(s);
	return (ret - 1);
}

int	print_uint(unsigned int u)
{
	char	*s;
	int		ret;

	s = ft_itoa_u(u);
	ret = write(1, s, ft_strlen(s));
	free(s);
	return (ret - 1);
}

int	print_int(int d, char arg)
{
	char	*s;
	int		ret;

	if (arg == 'c')
	{
		print_char(d);
		return (0);
	}
	s = ft_itoa(d);
	ret = write(1, s, ft_strlen(s));
	free(s);
	return (ret - 1);
}
