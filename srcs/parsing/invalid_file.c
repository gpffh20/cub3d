/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:18:52 by gykoh             #+#    #+#             */
/*   Updated: 2024/03/20 09:18:52 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	invalid_file(char *file_name)
{
	int		len;
	char	*tmp;

	len = ft_strlen(file_name);
	tmp = ft_substr(file_name, len - 4, 4);
	if (ft_strncmp(tmp, ".cub", 4) == 0)
	{
		free(tmp);
		return ;
	}
	free(tmp);
	error_exit("Error: map extension error.");
}
