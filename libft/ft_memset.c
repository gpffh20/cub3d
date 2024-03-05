/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 22:44:19 by gykoh             #+#    #+#             */
/*   Updated: 2023/05/19 17:05:07 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*tmp_b;
	unsigned char	tmp_c;

	i = 0;
	tmp_b = (unsigned char *)b;
	tmp_c = (unsigned char)c;
	while (i < len)
	{
		tmp_b[i] = tmp_c;
		i++;
	}
	return (b);
}
