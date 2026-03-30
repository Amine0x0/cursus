/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:33:15 by amabbadi          #+#    #+#             */
/*   Updated: 2025/07/25 06:27:47 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	error_found(enum e_ERRORS err)
{
	if (err == PARSING)
		return (printf(RED "error found in parsing.\n" RESET), true);
	else if (err == INIT)
		return (printf(RED "error initializing data.\n" RESET), true);
	else if (err == MALLOC)
		return (printf(RED "error in mallocating resources.\n" RESET), true);
	else if (err == THREAD)
		return (printf(RED "error in thread creation.\n" RESET), true);
	else
		return (false);
}
