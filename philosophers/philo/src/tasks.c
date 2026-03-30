/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:33:54 by amabbadi          #+#    #+#             */
/*   Updated: 2025/07/26 01:57:20 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	think(t_philo *philo)
{
	unsigned int	think_time;

	think_time = 100 + (philo->id % 5) * 100;
	print_log(philo, "is thinking");
	precise_usleep(think_time, philo->data);
}

bool	handle_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_log(philo, "has taken a fork");
	while (!get_someone_died(philo->data))
		precise_usleep(1000, philo->data);
	pthread_mutex_unlock(philo->left_fork);
	return (false);
}

void	eat(t_philo *philo)
{
	print_log(philo, "is eating");
	pthread_mutex_lock(&philo->state_mutex);
	philo->last_meal = timestamp_now();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->state_mutex);
	precise_usleep(philo->data->time_eat * 1000, philo->data);
}

void	philo_sleep(t_philo *philo)
{
	print_log(philo, "is sleeping");
	precise_usleep(philo->data->time_sleep * 1000, philo->data);
}
