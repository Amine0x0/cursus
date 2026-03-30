/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:34:04 by amabbadi          #+#    #+#             */
/*   Updated: 2025/07/26 22:18:30 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned int	timestamp_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	usleep_(t_philo *philo, unsigned int microsec)
{
	unsigned int	start;
	unsigned int	elapsed;
	unsigned int	target_ms;

	start = timestamp_now();
	target_ms = microsec / 1000;
	while (!get_someone_died(philo->data))
	{
		elapsed = timestamp_now() - start;
		if (elapsed >= target_ms)
			break ;
		usleep(100);
	}
}

void	precise_usleep(unsigned int microsec, t_data *data)
{
	unsigned int	start;
	unsigned int	elapsed;
	unsigned int	target_ms;

	start = timestamp_now();
	target_ms = microsec / 1000;
	while (!get_someone_died(data))
	{
		elapsed = timestamp_now() - start;
		if (elapsed >= target_ms)
			break ;
		usleep(10);
	}
}
