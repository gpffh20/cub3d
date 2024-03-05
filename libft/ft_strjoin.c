/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:59:25 by gykoh             #+#    #+#             */
/*   Updated: 2023/10/08 15:50:55 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*answer;
	size_t	s1_len;
	size_t	s2_len;
	size_t	total_size;

	if (s1 == 0 || s2 == 0)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	total_size = s1_len + s2_len + 1;
	answer = (char *)malloc(sizeof(char) * total_size);
	if (!answer)
		return (0);
	ft_strlcpy(answer, s1, total_size);
	ft_strlcpy(answer + s1_len, s2, total_size - s1_len);
	return (answer);
}
