/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 01:33:12 by amabbadi          #+#    #+#             */
/*   Updated: 2025/07/26 02:26:08 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	select_forks(t_philo *philo, pthread_mutex_t **first,
		pthread_mutex_t **second)
{
	int	left_index;
	int	right_index;

	left_index = philo->id - 1;
	right_index = philo->id % philo->data->nb_philo;
	if (left_index < right_index)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
}

bool	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (get_someone_died(philo->data))
		return (false);
	if (philo->data->nb_philo == 1)
		return (handle_one_philo(philo));
	select_forks(philo, &first, &second);
	pthread_mutex_lock(first);
	if (get_someone_died(philo->data))
	{
		pthread_mutex_unlock(first);
		return (false);
	}
	print_log(philo, "has taken a fork");
	pthread_mutex_lock(second);
	if (get_someone_died(philo->data))
	{
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(first);
		return (false);
	}
	print_log(philo, "has taken a fork");
	return (true);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->data->nb_philo == 1)
		return ;
	select_forks(philo, &first_fork, &second_fork);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}
