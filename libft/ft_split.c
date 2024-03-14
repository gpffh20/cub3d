/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:59:15 by gykoh             #+#    #+#             */
/*   Updated: 2023/05/15 22:44:20 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	if (n == 0)
		return (0);
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (0);
	while (i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	**ft_free(char **answer)
{
	size_t	i;

	i = 0;
	while (answer[i])
	{
		free(answer[i]);
		i++;
	}
	free(answer);
	return (0);
}

static size_t	ft_word_cnt(char const *s, char c)
{
	size_t	word_cnt;
	size_t	i;

	i = 0;
	word_cnt = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 && s[i] != c)
			|| (s[i] == c && s[i + 1] != '\0' && s[i + 1] != c))
			word_cnt++;
		i++;
	}
	return (word_cnt);
}

char	**ft_split(char const *s, char c)
{
	char	**answer;
	size_t	i;
	size_t	tmp;
	size_t	save;

	i = 0;
	tmp = 0;
	answer = (char **)malloc(sizeof(char *) * (ft_word_cnt(s, c) + 1));
	if (!answer)
		return (0);
	while (i < ft_word_cnt(s, c) && s[tmp] != '\0')
	{
		while (s[tmp] == c)
			tmp++;
		save = tmp;
		while (s[tmp] != c && s[tmp] != '\0')
			tmp++;
		answer[i] = ft_strndup(&s[save], tmp - save);
		if (answer[i++] == 0)
			return (ft_free(answer));
	}
	answer[i] = 0;
	return (answer);
}
