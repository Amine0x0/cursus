/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:33:22 by amabbadi          #+#    #+#             */
/*   Updated: 2025/07/16 22:11:52 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_metadata(t_meta *meta)
{
	int	i;

	i = 0;
	while (i < meta->argc)
	{
		free(meta->argv[i]);
		i++;
	}
	free(meta->argv);
}

bool	free_ressources(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].state_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->death);
	pthread_mutex_destroy(&data->meal_check);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
	return (true);
}
