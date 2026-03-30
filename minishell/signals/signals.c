/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 11:40:35 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/05 05:34:50 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	handle_signals(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	msh_signals(void)
{
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;
}

void	disable_parent_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	restore_parent_signals(void)
{
	msh_signals();
}
