/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:00:26 by gykoh             #+#    #+#             */
/*   Updated: 2023/10/08 15:56:49 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read_line(int fd, char *storage)
{
	ssize_t	read_size;
	char	buff[BUFFER_SIZE + 1];
	char	*tmp;

	read_size = 1;
	while (read_size > 0)
	{
		read_size = read(fd, buff, BUFFER_SIZE);
		if (read_size < 0)
		{
			free(storage);
			return (NULL);
		}
		buff[read_size] = '\0';
		tmp = storage;
		if (!tmp)
			tmp = ft_strdup("");
		storage = ft_strjoin(tmp, buff);
		free(tmp);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (storage);
}

char	*ft_extract_line(char **storage)
{
	size_t	line_len;
	char	*line;
	char	*newline_pos;
	char	*tmp;

	line_len = ft_strlen(*storage);
	newline_pos = ft_strchr(*storage, '\n');
	tmp = *storage;
	if (newline_pos)
		line_len = newline_pos - *storage + 1;
	line = (char *)malloc(sizeof(char) * (line_len + 1));
	if (!line)
	{
		free(*storage);
		*storage = NULL;
		return (NULL);
	}
	ft_strlcpy(line, *storage, line_len + 1);
	*storage = NULL;
	if (newline_pos)
		*storage = ft_strdup(newline_pos + 1);
	free(tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage = ft_read_line(fd, storage);
	if (storage == NULL || *storage == 0)
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}
	line = ft_extract_line(&storage);
	return (line);
}
