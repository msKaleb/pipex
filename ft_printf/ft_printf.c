/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:32:26 by msoria-j          #+#    #+#             */
/*   Updated: 2022/12/20 13:11:15 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

static int	print_adr(unsigned long long p)
{
	char	*s;
	int		ret;

	if (p < 0)
		p = p * -1;
	s = change_base(p, 'p');
	write(1, "0x", 2);
	ret = write(1, s, ft_strlen(s)) + 1;
	free(s);
	return (ret);
}

static int	choose_format(va_list ap, char format)
{
	int	ret;

	ret = 0;
	if (format == '%')
		write (1, "%%", 1);
	if (format == 'd' || format == 'i' || format == 'c')
		ret += print_int(va_arg(ap, int), format);
	if (format == 's')
		ret += print_str(va_arg(ap, char *));
	if (format == 'x' || format == 'X')
		ret += print_hex(va_arg(ap, unsigned int), format);
	if (format == 'p')
		ret += print_adr(va_arg(ap, unsigned long long));
	if (format == 'u')
		ret += print_uint(va_arg(ap, unsigned int));
	return (ret);
}

int	ft_printf(char const *format, ...)
{
	va_list			ap;
	int				ret;

	ret = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format != '%')
			write (1, (unsigned char *)format, 1);
		if (*format == '%')
		{
			format++;
			ret += choose_format(ap, *format);
		}
		format++;
		ret++;
	}
	va_end(ap);
	return (ret);
}

/*
#include<stdio.h>

int	main(void)
{
	unsigned int	u;
	char			c;
	char			s[] = "test ft_printf";
	int				d;
	int				pret;

	c = 'z';
	d = -12;
	u = 69548;
	pret = printf("   printf: %c | %i | %x | %X | %s | %p", c, d, u, u, s, &c);
	//pret = printf("Porque putnbr() y putstr()\t no son suficientes");
	//pret = printf("   printf: %X %%%%", u);
	printf("\tres: %d\n", pret);
	pret = ft_printf("ft_printf: %c | %i | %x | %X | %s | %p", c, d, u, u, s, &c);
	//pret = ft_printf("Porque putnbr() y putstr()\t no son suficientes");
	//pret = ft_printf("ft_printf: %X %%%%", u);
	ft_printf("\tres: %d\n", pret);
}
*/