#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <pthread.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define TAKE_FORK 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DEAD 4
# define DONE 5

struct	s_data;

typedef struct s_philo
{
	int				pos;
	int				eating;
	uint64_t		last_eat;
	int				eat_count;
	struct s_data	*data;
	sem_t			*mutex;
	sem_t			*eat_mutex;
}				t_philo;

typedef struct s_data
{
	int			count;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat;
	uint64_t	start;
	t_philo		*philos;
	sem_t		*write_mutex;
	sem_t		*dead_mutex;
	sem_t		*fork_mutex;
}				t_data;

void		exit_message(t_data *data, char *str, int status);
void		routine(t_philo *arg);
int			ft_atoi(const char *nptr);
int			ft_strlen(char const *str);
void		init_threads(t_data *data, t_philo *philos);
void		mutex_init(t_data *data);
void		init_philos(t_data *data, t_philo *philos);
void		init(t_data *data, int ac, char **av);
void		message(t_data *data, t_philo *philo, int type);
void		eat(t_philo *philo);
void		sleeep(t_philo *philo);
void		*must_eat(void *arg);
void		*death(void *arg);
void		take_forks(t_philo *philo);
uint64_t	get_time(void);
void		free_all(t_data *data);

#endif
