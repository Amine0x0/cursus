/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:33:33 by amabbadi          #+#    #+#             */
/*   Updated: 2025/07/25 02:04:36 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_task,
				&data->philos[i]) != 0)
		{
			set_someone_died(data, true);
			while (i > 0)
				pthread_join(data->philos[--i].thread, NULL);
			free_ressources(data);
			return (error_found(THREAD), 1);
		}
		i++;
	}
	return (0);
}

static void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
		pthread_join(data->philos[i++].thread, NULL);
}

static int	init_and_start(t_meta *meta, t_data *data)
{
	if (!init_data(data, meta))
		return (free_metadata(meta), error_found(INIT), 1);
	if (!allocate_resources(data))
		return (free_metadata(meta), 1);
	data->start_time = timestamp_now();
	assign_forks(data);
	return (0);
}

static int	create_death_thread(t_data *data, pthread_t *death_thread)
{
	if (pthread_create(death_thread, NULL, death_checker, data) != 0)
	{
		set_someone_died(data, true);
		join_threads(data);
		free_ressources(data);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_meta		meta;
	t_data		data;
	pthread_t	death_thread;

	if (!parse_check(argc - 1, argv + 1, &meta))
		return (error_found(PARSING), 1);
	if (init_and_start(&meta, &data))
		return (1);
	if (create_threads(&data))
		return (free_metadata(&meta), 1);
	if (create_death_thread(&data, &death_thread))
		return (free_metadata(&meta), error_found(THREAD), 1);
	pthread_join(death_thread, NULL);
	join_threads(&data);
	free_ressources(&data);
	free_metadata(&meta);
	return (0);
}
