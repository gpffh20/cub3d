/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:24:09 by gykoh             #+#    #+#             */
/*   Updated: 2023/04/30 15:53:34 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*answer;
	unsigned int	i;

	i = 0;
	if (s == 0 || f == 0)
		return (0);
	answer = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (answer == 0)
		return (0);
	while (s[i] != '\0')
	{
		answer[i] = f(i, s[i]);
		i++;
	}
	answer[i] = '\0';
	return (answer);
}
