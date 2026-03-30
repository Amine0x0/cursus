/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resources.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:33:44 by amabbadi          #+#    #+#             */
/*   Updated: 2025/07/24 22:57:35 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	init_forks_mutexes(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			j = 0;
			while (j < i)
			{
				pthread_mutex_destroy(&data->forks[j]);
				j++;
			}
			return (error_found(THREAD), false);
		}
		i++;
	}
	return (true);
}

static bool	init_philos_mutexes(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->philos[i].state_mutex, NULL) != 0)
		{
			j = 0;
			while (j < i)
			{
				pthread_mutex_destroy(&data->philos[j].state_mutex);
				j++;
			}
			j = 0;
			while (j < data->nb_philo)
			{
				pthread_mutex_destroy(&data->forks[j]);
				j++;
			}
			return (error_found(THREAD), false);
		}
		i++;
	}
	return (true);
}

bool	allocate_resources(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (error_found(MALLOC), false);
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
	{
		free(data->forks);
		return (error_found(MALLOC), false);
	}
	if (!init_forks_mutexes(data))
	{
		free(data->forks);
		free(data->philos);
		return (false);
	}
	if (!init_philos_mutexes(data))
	{
		free(data->forks);
		free(data->philos);
		return (false);
	}
	return (true);
}

void	assign_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		i++;
	}
}
