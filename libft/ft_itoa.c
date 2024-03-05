/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:59:18 by gykoh             #+#    #+#             */
/*   Updated: 2023/05/08 22:21:27 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_calc_len(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	long	nb;
	char	*answer;

	len = ft_calc_len(n);
	nb = n;
	answer = (char *)malloc(sizeof(char) * (len + 1));
	if (!answer)
		return (0);
	if (nb < 0)
	{
		answer[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		answer[0] = '0';
	answer[len--] = '\0';
	while (nb != 0)
	{
		answer[len] = nb % 10 + '0';
		len--;
		nb /= 10;
	}
	return (answer);
}
