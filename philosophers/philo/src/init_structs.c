/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:33:27 by amabbadi          #+#    #+#             */
/*   Updated: 2025/07/25 02:04:17 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	init_data_values(t_data *data, t_meta *metadata)
{
	data->nb_philo = ft_atoi(metadata->argv[0]);
	data->time_die = ft_atoi(metadata->argv[1]);
	data->time_eat = ft_atoi(metadata->argv[2]);
	data->time_sleep = ft_atoi(metadata->argv[3]);
	if (metadata->argc == 5)
		data->must_eat_count = ft_atoi(metadata->argv[4]);
	else
		data->must_eat_count = -1;
	data->someone_died = false;
	data->start_time = 0;
	data->forks = NULL;
	data->philos = NULL;
	data->finished_count = 0;
}

static bool	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->print, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&data->death, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print);
		return (false);
	}
	if (pthread_mutex_init(&data->meal_check, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print);
		pthread_mutex_destroy(&data->death);
		return (false);
	}
	return (true);
}

bool	init_data(t_data *data, t_meta *metadata)
{
	init_data_values(data, metadata);
	return (init_mutexes(data));
}
