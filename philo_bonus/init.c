#include "philo_bonus.h"

void	init_threads(t_data *data, t_philo *philos)
{
	int			i;
	pthread_t	tid;
	int			p;

	i = 0;
	p = 1;
	data->start = get_time();
	while (p != 0 && i <= data->count - 1)
	{
		philos[i].last_eat = data->start;
		p = fork();
		if (p == 0)
			routine(&philos[i]);
		++i;
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
	data->write_mutex = sem_open("write_mutex", 0777, O_CREAT, 1);
	data->dead_mutex = sem_open("dead_mutex", 0777, O_CREAT, 0);
	data->fork_mutex = sem_open("fork_mutex", 0777, O_CREAT, data->count);
}

void	init_philos(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < data->count)
	{
		philos[i].pos = i + 1;
		philos[i].eating = 0;
		philos[i].eat_count = 0;
		philos[i].data = data;
		philos[i].mutex = sem_open("mutex", 0777, O_CREAT, 1);
		philos[i].eat_mutex = sem_open("eat_mutex", 0777, O_CREAT, 0);
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
	if (data->count < 1 || data->count > 200 || data->time_to_die < 60
		|| data->time_to_eat < 60 || data->time_to_sleep < 60
		|| data->must_eat < 0)
		exit_message(data, "Error. Wrong arguments\n", EXIT_FAILURE);
	data->philos = malloc(sizeof(t_philo) * data->count);
	if (!data->philos)
		exit_message(data, "Error during malloc\n", EXIT_FAILURE);
	init_philos(data, data->philos);
	mutex_init(data);
}
