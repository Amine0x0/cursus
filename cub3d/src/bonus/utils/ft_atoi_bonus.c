/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 04:55:04 by amabbadi          #+#    #+#             */
/*   Updated: 2025/12/29 19:17:07 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	ft_atoi(char *str)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		r = r * 10 + str[i] - 48;
		if (r > 255 || r < 0)
			return (-1);
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (r);
}
