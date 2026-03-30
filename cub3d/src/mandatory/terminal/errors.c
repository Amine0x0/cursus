/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 05:41:36 by amabbadi          #+#    #+#             */
/*   Updated: 2025/12/31 09:19:04 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	err(t_errors type, char *reason)
{
	if (!reason)
		reason = "unknown error";
	if (type == INIT)
		printf("initialization error: reason [%s]\n", reason);
	else if (type == ARGS)
		printf("bad arg count: reason [%s]\n", reason);
	else if (type == MAP)
		printf("error in map: reason [%s]\n", reason);
}
