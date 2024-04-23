#include "../headers/philo.h"

static void one_philosopher(t_data *data, t_list *philo)
{
    if (philo->nb_philo == 1)
    {
		if (current_time(philo) < philo->time_to_die)
		{
			pthread_mutex_lock(philo->right_fork);
			print_message(current_time(philo), philo->id, "has taken a fork\n", data);
			usleep(philo->time_to_die * 1000);
			pthread_mutex_unlock(philo->right_fork);
			philo_death(philo, data);
		}
    }
}

static int    even_philosophers(t_list *philo, t_data *data)
{
    pthread_mutex_lock(philo->left_fork);
    if (eat_or_dead(data, philo))
    {
        if ((current_time(philo) - philo->last_meal) >= philo->time_to_die)
        {
            pthread_mutex_unlock(philo->left_fork);
            return (philo_death(philo, data), 0);
        }
        if (!eat_or_dead(data, philo))
            return (pthread_mutex_unlock(philo->left_fork), 0);
        print_message(current_time(philo), philo->id, "has taken a fork\n", data);
        pthread_mutex_lock(philo->right_fork);
        print_message(current_time(philo), philo->id, "has taken a fork\n", data);
        print_message(current_time(philo), philo->id, "is eating\n", data);
        philo->nb_meals++;
        philo->last_meal = current_time(philo);
        usleep(philo->time_to_eat * 1000);
        meals_eaten(data, philo);
        pthread_mutex_unlock(philo->right_fork);
    }
    pthread_mutex_unlock(philo->left_fork);
    return (1);
}

static int    odd_philosophers(t_list *philo, t_data *data)
{
	pthread_mutex_lock(philo->right_fork);
    if (eat_or_dead(data, philo))
    {
        if ((current_time(philo) - philo->last_meal) >= philo->time_to_die)
        {
            pthread_mutex_unlock(philo->right_fork);
            return (philo_death(philo, data), 0);
        }
        if (!eat_or_dead(data, philo))
            return (pthread_mutex_unlock(philo->right_fork), 0);
        print_message(current_time(philo), philo->id, "has taken a fork\n", data);
        pthread_mutex_lock(philo->left_fork);
        print_message(current_time(philo), philo->id, "has taken a fork\n", data);
        print_message(current_time(philo), philo->id, "is eating\n", data);
        philo->nb_meals++;
        philo->last_meal = current_time(philo);
        usleep(philo->time_to_eat * 1000);
        meals_eaten(data, philo);
        pthread_mutex_unlock(philo->left_fork);
    }
    pthread_mutex_unlock(philo->right_fork);
    return (1);
}

static int even_or_odd(t_list *philo, t_data *data)
{
    if (eat_or_dead(data, philo))
    {
        if ((current_time(philo) - philo->last_meal) >= philo->time_to_die)
            return (philo_death(philo, data), 0);
        if (!eat_or_dead(data, philo))
            return (0);
        if (philo->id % 2 == 0)
        {
            if (!even_philosophers(philo, data))
                return (0);
        }
        else
        {
            if (!odd_philosophers(philo, data))
                return (0);
        }
    }
    return (1);
}

void    *ft_threads(void *arg)
{
    t_list *philo;
    t_data *data;

    philo = (t_list *)arg;
    data = philo->data;
    one_philosopher(data, philo);
    while(eat_or_dead(data, philo))
    {
        if (!even_or_odd(philo, data))
            break;
        if (!eat_or_dead(data, philo))
            break;
        print_message(current_time(philo), philo->id, "is sleeping\n", data);
        usleep(philo->time_to_sleep * 1000);
        if (eat_or_dead(data, philo))
        {
            if ((current_time(philo) - philo->last_meal) >= philo->time_to_die)
                return (philo_death(philo, data), arg);
            if (!eat_or_dead(data, philo))
                break;
            print_message(current_time(philo), philo->id, "is thinking\n", data);
        }
    }
    return (arg);
}
