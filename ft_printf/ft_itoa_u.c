/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 20:54:27 by msoria-j          #+#    #+#             */
/*   Updated: 2022/12/15 17:34:47 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

static int	count_digits(long n)
{
	unsigned long	number;
	int				digits;

	digits = 1;
	number = (unsigned long)n;
	if (n < 0)
	{
		number = number * -1;
		digits++;
	}
	while (number / 10 > 0)
	{
		number /= 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa_u(unsigned int n)
{
	unsigned int	number;
	int				digits;
	long			neg;
	char			*str;

	neg = 0;
	digits = count_digits(n);
	str = ft_calloc(1, digits + 1);
	number = (unsigned int) n;
	if (n < 0)
	{
		number = number * -1;
		neg = 1;
	}
	if (!str)
		return (NULL);
	while (digits--)
	{
		str[digits] = (number % 10) + '0';
		number /= 10;
	}
	return (str);
}
