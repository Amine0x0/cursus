/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_task.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 01:20:16 by amabbadi          #+#    #+#             */
/*   Updated: 2025/07/26 01:01:43 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	should_finish(t_philo *philo)
{
	if (has_eaten_enough(philo))
	{
		mark_finished(philo);
		return (true);
	}
	return (false);
}

static bool	handle_eating_cycle(t_philo *philo)
{
	if (!take_forks(philo))
		return (false);
	if (get_someone_died(philo->data))
	{
		drop_forks(philo);
		return (false);
	}
	eat(philo);
	drop_forks(philo);
	return (true);
}

static void	philo_main_loop(t_philo *philo)
{
	while (!get_someone_died(philo->data))
	{
		if (should_finish(philo))
			break ;
		think(philo);
		if (get_someone_died(philo->data))
			break ;
		if (!handle_eating_cycle(philo))
			continue ;
		if (should_finish(philo))
			break ;
		if (!get_someone_died(philo->data))
			philo_sleep(philo);
	}
}

void	*philo_task(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		precise_usleep(1000, philo->data);
	philo_main_loop(philo);
	return (NULL);
}
