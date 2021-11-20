#include "philo.h"

void	exit_message(t_data *data, char *str, int status)
{
	write(2, str, ft_strlen(str));
	free_all(data);
	exit(status);
}

void	*must_eat(void *arg)
{
	int		i;
	int		count;
	t_data	*data;

	count = 0;
	data = (t_data *)arg;
	while (count < data->must_eat)
	{
		i = -1;
		while (++i < data->count)
			pthread_mutex_lock(&data->philos[i].eat_mutex);
		++count;
	}
	message(data, NULL, DONE);
	pthread_mutex_unlock(&data->dead_mutex);
	return ((void *)0);
}

void	*death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		if (!philo->eating
			&& get_time() > philo->last_eat + philo->data->time_to_die)
		{
			message(philo->data, philo, DEAD);
			pthread_mutex_unlock(&philo->data->dead_mutex);
			return ((void *)0);
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(1000);
	}
}

void	*routine(void *arg)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *)arg;
	if (pthread_create(&tid, NULL, &death, (void *)philo))
		exit_message(NULL, "Could not create thread\n", EXIT_FAILURE);
	pthread_detach(tid);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		sleeep(philo);
		message(philo->data, philo, THINKING);
	}
	return ((void *)0);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 5 && ac != 6)
		exit_message(NULL, "Error. Wrong number of arguments\n", EXIT_FAILURE);
	data = malloc(sizeof(t_data));
	if (!data)
		exit_message(NULL, "Error during malloc\n", EXIT_FAILURE);
	init(data, ac, av);
	init_threads(data, data->philos);
	pthread_mutex_lock(&data->dead_mutex);
	return (0);
}
