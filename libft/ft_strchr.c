/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 15:58:42 by gykoh             #+#    #+#             */
/*   Updated: 2023/05/19 17:07:53 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	tmp_c;

	i = 0;
	tmp_c = (char)c;
	while (s[i] != '\0' && s[i] != tmp_c)
		i++;
	if (s[i] == tmp_c)
		return ((char *)(s + i));
	return (0);
}
