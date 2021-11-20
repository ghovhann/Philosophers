#include "philo_bonus.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->fork_mutex);
	sem_wait(philo->data->fork_mutex);
	message(philo->data, philo, TAKE_FORK);
}

void	eat(t_philo *philo)
{
	sem_wait(philo->mutex);
	philo->eating = 1;
	philo->last_eat = get_time();
	message(philo->data, philo, EATING);
	sem_post(philo->mutex);
	usleep(philo->data->time_to_eat * 1000);
	philo->eat_count++;
	philo->eating = 0;
	sem_post(philo->eat_mutex);
}

void	sleeep(t_philo *philo)
{
	sem_post(philo->data->fork_mutex);
	sem_post(philo->data->fork_mutex);
	message(philo->data, philo, SLEEPING);
	usleep(philo->data->time_to_sleep * 1000);
}
