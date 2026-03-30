/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 00:50:37 by amabbadi          #+#    #+#             */
/*   Updated: 2025/07/26 01:49:51 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# define FT_ATOL_ERROR -9223372036854775807L
# define RED "\x1b[31m"
# define RESET "\x1b[0m"

typedef struct s_meta
{
	int				argc;
	char			**argv;
}					t_meta;

struct	s_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	state_mutex;
	long long		last_meal;
	int				meals_eaten;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat_count;
	bool			someone_died;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	t_philo			*philos;
	int				finished_count;
	pthread_mutex_t	meal_check;
}					t_data;

enum				e_ERRORS
{
	PARSING,
	INIT,
	MALLOC,
	THREAD,
};

// Fixed function prototypes
bool				parse_check(int argc, char **argv, t_meta *meta);
bool				error_found(enum e_ERRORS err);
bool				is_arg_valid(char *arg);
bool				fill_metadata(int argc, char **argv, t_meta *meta);
bool				init_data(t_data *data, t_meta *metadata);
bool				allocate_resources(t_data *data);
void				assign_forks(t_data *data);
bool				free_ressources(t_data *data);
void				*philo_task(void *arg);
void				print_log(t_philo *philo, char *msg);
unsigned int		timestamp_now(void);
void				usleep_(t_philo *philo, unsigned int microsec);
void				philo_sleep(t_philo *philo);
void				drop_forks(t_philo *philo);
void				eat(t_philo *philo);
bool				take_forks(t_philo *philo);
void				think(t_philo *philo);
void				*death_checker(void *arg);
bool				get_someone_died(t_data *data);
void				set_someone_died(t_data *data, bool val);
void				mark_finished(t_philo *philo);
bool				has_eaten_enough(t_philo *philo);
bool				handle_one_philo(t_philo *philo);
void				free_metadata(t_meta *meta);
int					ft_isdigit(int c);
char				*ft_strdup(char *src);
int					ft_atoi(const char *str);
int					ft_strcmp(const char *s1, const char *s2);
long				ft_atol(const char *str);
void				precise_usleep(unsigned int microsec, t_data *data);

#endif