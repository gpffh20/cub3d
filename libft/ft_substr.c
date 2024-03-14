/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:52:48 by gykoh             #+#    #+#             */
/*   Updated: 2023/05/19 20:02:03 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*answer;

	if (!s)
		return (0);
	if (ft_strlen(s) <= (size_t)start)
		return (ft_strdup(""));
	if (ft_strlen(s) < len + start)
		len = ft_strlen(s) - start;
	answer = (char *)malloc(sizeof(char) * (len + 1));
	if (!answer)
		return (0);
	ft_strlcpy(answer, s + start, len + 1);
	return (answer);
}
