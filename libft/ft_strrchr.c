/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 16:10:11 by gykoh             #+#    #+#             */
/*   Updated: 2023/05/19 18:09:06 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	tmp_c;

	i = ft_strlen(s);
	tmp_c = (char)c;
	while (i > 0 && s[i] != tmp_c)
		i--;
	if (s[i] == tmp_c)
		return ((char *)(s + i));
	return (0);
}
