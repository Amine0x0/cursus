/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:07:22 by ylabser           #+#    #+#             */
/*   Updated: 2025/08/03 03:28:19 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	print_error(const char *context, const char *message)
{
	if (context)
	{
		print_err("minishell: %s: ", context);
		print_err("%s\n", message);
	}
	else
		print_err("minishell: %s\n", message);
}

int	syntax_error(char *mssg)
{
	print_err("%s\n", mssg);
	return (0);
}
