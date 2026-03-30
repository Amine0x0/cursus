/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 00:59:03 by amabbadi          #+#    #+#             */
/*   Updated: 2025/07/26 22:20:03 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	mark_finished(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_check);
	philo->data->finished_count++;
	pthread_mutex_unlock(&philo->data->meal_check);
}

void	print_log(t_philo *philo, char *msg)
{
	bool			is_death_msg;
	unsigned int	t;

	is_death_msg = (ft_strcmp(msg, "died") == 0);
	pthread_mutex_lock(&philo->data->print);
	if (is_death_msg || !get_someone_died(philo->data))
	{
		t = timestamp_now() - philo->data->start_time;
		printf("%u %d %s\n", t, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->print);
}

bool	get_someone_died(t_data *data)
{
	bool	died;

	pthread_mutex_lock(&data->death);
	died = data->someone_died;
	pthread_mutex_unlock(&data->death);
	return (died);
}

void	set_someone_died(t_data *data, bool val)
{
	pthread_mutex_lock(&data->death);
	data->someone_died = val;
	pthread_mutex_unlock(&data->death);
}

bool	has_eaten_enough(t_philo *philo)
{
	bool	enough;

	pthread_mutex_lock(&philo->state_mutex);
	enough = (philo->data->must_eat_count != -1
			&& philo->meals_eaten >= philo->data->must_eat_count);
	pthread_mutex_unlock(&philo->state_mutex);
	return (enough);
}
