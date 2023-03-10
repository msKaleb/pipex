/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:28:56 by msoria-j          #+#    #+#             */
/*   Updated: 2022/12/18 19:29:43 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include<stdarg.h>
# include<unistd.h>
# include"./libft/libft.h"

char	*change_base(unsigned long long nbr, char base);
char	*ft_itoa_u(unsigned int n);
int		print_char(char c);
int		print_str(char *s);
int		print_hex(unsigned int p, char format);
int		print_uint(unsigned int u);
int		print_int(int d, char arg);
int		ft_printf(char const *format, ...);

#endif