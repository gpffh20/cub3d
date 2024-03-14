/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:30:42 by gykoh             #+#    #+#             */
/*   Updated: 2023/10/08 15:39:42 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check(char c, va_list *args)
{
	if (c == 'c')
		return (ft_putchar_pf(va_arg(*args, int)));
	else if (c == 's')
		return (ft_putstr_pf(va_arg(*args, char *)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr_pf(va_arg(*args, int)));
	else if (c == 'u')
		return (ft_putnbr_pf(va_arg(*args, unsigned int)));
	else if (c == 'x')
		return (ft_puthex_pf(va_arg(*args, unsigned int), 0));
	else if (c == 'X')
		return (ft_puthex_pf(va_arg(*args, unsigned int), 1));
	else if (c == 'p')
		return (ft_putaddr_pf(va_arg(*args, unsigned long)));
	else if (c == '%')
		return (ft_putchar_pf('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		len;
	va_list	args;

	i = 0;
	len = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			len += ft_check(format[i + 1], &args);
			i++;
		}
		else
			len += write(1, &format[i], 1);
		i++;
	}
	va_end(args);
	return (len);
}
