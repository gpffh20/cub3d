/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:30:46 by gykoh             #+#    #+#             */
/*   Updated: 2023/10/08 15:40:43 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_pf(char c)
{
	int	len;

	len = write(1, &c, 1);
	return (len);
}

int	ft_putstr_pf(char *str)
{
	int	len;

	len = 0;
	if (!str)
		str = "(null)";
	while (*str)
		len += write(1, str++, 1);
	return (len);
}

int	ft_putnbr_pf(long long n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		len += ft_putchar_pf('-');
		n *= -1;
	}
	if (n >= 10)
		len += ft_putnbr_pf(n / 10);
	len += ft_putchar_pf(n % 10 + '0');
	return (len);
}

int	ft_puthex_pf(unsigned long n, int flag)
{
	int		len;
	char	*base;

	len = 0;
	if (flag == 0)
		base = "0123456789abcdef";
	if (flag == 1)
		base = "0123456789ABCDEF";
	if (n >= 16)
		len += ft_puthex_pf((n / 16), flag);
	len += ft_putchar_pf(base[n % 16]);
	return (len);
}

int	ft_putaddr_pf(unsigned long n)
{
	int	len;

	len = 0;
	len += ft_putstr_pf("0x");
	len += ft_puthex_pf(n, 0);
	return (len);
}
