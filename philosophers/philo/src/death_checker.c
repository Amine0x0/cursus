/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:33:10 by amabbadi          #+#    #+#             */
/*   Updated: 2025/07/26 22:20:45 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	check_all_finished(t_data *data)
{
	bool	done;

	pthread_mutex_lock(&data->meal_check);
	done = (data->must_eat_count != -1
			&& data->finished_count >= data->nb_philo);
	pthread_mutex_unlock(&data->meal_check);
	if (done)
		set_someone_died(data, true);
	return (done);
}

static bool	check_philo_death(t_data *data, int i)
{
	unsigned int	now;
	unsigned int	last_meal;
	bool			died;

	died = false;
	pthread_mutex_lock(&data->philos[i].state_mutex);
	now = timestamp_now();
	last_meal = data->philos[i].last_meal;
	if (now - last_meal > (unsigned int)data->time_die)
		died = true;
	pthread_mutex_unlock(&data->philos[i].state_mutex);
	if (died)
	{
		set_someone_died(data, true);
		print_log(&data->philos[i], "died");
		return (true);
	}
	return (false);
}

static bool	check_all_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (check_philo_death(data, i))
			return (true);
		i++;
	}
	return (false);
}

void	*death_checker(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	if (data->nb_philo == 1)
	{
		usleep_(data->philos, data->time_die * 1000);
		set_someone_died(data, true);
		print_log(&data->philos[0], "died");
		return (NULL);
	}
	while (!get_someone_died(data))
	{
		if (check_all_finished(data))
			break ;
		if (check_all_philos(data))
			break ;
		precise_usleep(1000, data);
	}
	return (NULL);
}
