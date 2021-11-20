/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghovhann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 13:49:03 by ghovhann          #+#    #+#             */
/*   Updated: 2021/07/20 13:49:05 by ghovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(const char *nptr)
{
	int	n;
	int	sign;

	n = 0;
	sign = 1;
	while (*nptr == ' ')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		n = n * 10 + (*nptr - '0');
		nptr++;
	}
	return (n * sign);
}

int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

uint64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	message(t_data *data, t_philo *philo, int type)
{
	static int	over = 0;

	sem_wait(data->write_mutex);
	if (!over)
	{
		printf("%lld\t", get_time() - data->start);
		if (type == TAKE_FORK)
			printf("%d has taken a fork\n", philo->pos);
		else if (type == EATING)
			printf("%d is eating\n", philo->pos);
		else if (type == SLEEPING)
			printf("%d is sleeping\n", philo->pos);
		else if (type == THINKING)
			printf("%d is thiking\n", philo->pos);
		else
		{
			if (type == DEAD)
				printf("%d died\n", philo->pos);
			if (type == DONE)
				printf("Must eat number was reached\n");
			kill(0, SIGINT);
			over = 1;
		}								
	}
	sem_post(data->write_mutex);
}

void	free_all(t_data *data)
{
	if (data)
	{
		if (data->philos)
		{
			sem_close(data->philos->mutex);
			sem_close(data->philos->eat_mutex);
			free(data->philos);
			sem_close(data->write_mutex);
			sem_close(data->dead_mutex);
		}
		sem_close(data->fork_mutex);
		free(data);
	}
}
