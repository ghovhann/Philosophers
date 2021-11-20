#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork_mutex[philo->lfork]);
	pthread_mutex_lock(&philo->data->fork_mutex[philo->rfork]);
	message(philo->data, philo, TAKE_FORK);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->eating = 1;
	philo->last_eat = get_time();
	message(philo->data, philo, EATING);
	usleep(philo->data->time_to_eat * 1000);
	philo->eat_count++;
	philo->eating = 0;
	pthread_mutex_unlock(&philo->eat_mutex);
	pthread_mutex_unlock(&philo->mutex);
}

void	sleeep(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->fork_mutex[philo->lfork]);
	pthread_mutex_unlock(&philo->data->fork_mutex[philo->rfork]);
	message(philo->data, philo, SLEEPING);
	usleep(philo->data->time_to_sleep * 1000);
}
