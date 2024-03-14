/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 19:39:06 by gykoh             #+#    #+#             */
/*   Updated: 2023/10/08 15:51:14 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		size;
	char	*answer;

	i = 0;
	size = ft_strlen(s1);
	answer = malloc(sizeof(char) * (size + 1));
	if (!answer)
		return (0);
	while (s1[i] != '\0')
	{
		answer[i] = s1[i];
		i++;
	}
	answer[i] = '\0';
	return (answer);
}
