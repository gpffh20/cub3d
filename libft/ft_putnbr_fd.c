/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:37:30 by gykoh             #+#    #+#             */
/*   Updated: 2023/05/19 17:06:05 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	write_recur(long long num, int fd)
{
	char	char_num;

	if (num < 0)
	{
		write (fd, "-", 1);
		num *= -1;
		write_recur(num, fd);
	}
	else if (num >= 10)
	{
		write_recur(num / 10, fd);
		write_recur(num % 10, fd);
	}
	else
	{
		char_num = num + '0';
		write (fd, &char_num, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	write_recur((long long)n, fd);
}
