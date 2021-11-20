#include "philo.h"

void	init_threads(t_data *data, t_philo *philos)
{
	pthread_t	tid;
	int			i;

	i = -1;
	data->start = get_time();
	while (++i < data->count)
	{
		philos[i].last_eat = data->start;
		if (pthread_create(&tid, NULL, &routine, (void *)&philos[i]))
			exit_message(NULL, "Could not create thread\n", EXIT_FAILURE);
		pthread_detach(tid);
	}
	if (data->must_eat > 0)
	{
		if (pthread_create(&tid, NULL, &must_eat, (void *)data))
			exit_message(NULL, "Could not create thread\n", EXIT_FAILURE);
		pthread_detach(tid);
	}
}

void	mutex_init(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->write_mutex, NULL);
	pthread_mutex_init(&data->dead_mutex, NULL);
	pthread_mutex_lock(&data->dead_mutex);
	data->fork_mutex = malloc(sizeof(pthread_mutex_t) * data->count);
	if (!data->fork_mutex)
		exit_message(data, "Error during malloc\n", EXIT_FAILURE);
	i = -1;
	while (++i < data->count)
		pthread_mutex_init(&data->fork_mutex[i], NULL);
}

void	init_philos(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < data->count)
	{
		philos[i].pos = i + 1;
		philos[i].eating = 0;
		philos[i].lfork = i;
		philos[i].rfork = (i + 1) % data->count;
		philos[i].eat_count = 0;
		philos[i].data = data;
		pthread_mutex_init(&philos[i].mutex, NULL);
		pthread_mutex_init(&philos[i].eat_mutex, NULL);
		pthread_mutex_lock(&philos[i].eat_mutex);
	}
}

void	init(t_data *data, int ac, char **av)
{
	data->count = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	else
		data->must_eat = 0;
	if (data->count <1 || data->count > 200 || data->time_to_die < 60
		|| data->time_to_eat < 60 || data->time_to_sleep < 60
		|| data->must_eat < 0)
		exit_message(data, "Error. Wrong arguments\n", EXIT_FAILURE);
	data->philos = malloc(sizeof(t_philo) * data->count);
	if (!data->philos)
		exit_message(data, "Error during malloc\n", EXIT_FAILURE);
	init_philos(data, data->philos);
	mutex_init(data);
}
