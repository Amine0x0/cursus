/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulah <maboulah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 00:08:42 by maboulah          #+#    #+#             */
/*   Updated: 2026/01/17 17:18:00 by maboulah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

bool	map_name(char *av)
{
	int	len;

	if (!av)
		return (0);
	len = (int)ft_strlen(av);
	if (len < 4)
		return (0);
	if (!ft_strcmp(&av[len - 4], ".cub"))
		return (1);
	return (0);
}

bool	check_map(t_game *game, char *av)
{
	if (!map_name(av) || !check_text(game) || !check_map1(game))
		return (0);
	return (1);
}
