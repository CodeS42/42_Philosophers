#include "../headers/philo.h"

void print_message(long time, int id, char *msg, t_data *data)
{
    pthread_mutex_lock(&data->message);
    printf("%ld %d %s", time, id, msg);
    pthread_mutex_unlock(&data->message);
}

void philo_death(t_list *philo, t_data *data)
{
    pthread_mutex_lock(&data->dead_m);
    data->dead = 1;
    print_message(current_time(philo), philo->id, "died\n", data);
    pthread_mutex_unlock(&data->dead_m);
}

void destroy_mutexes(t_data *data, char **argv)
{
    int i;

    i = 0;
    if (data->forks_mutex)
    {
        while (i < ft_atoi(argv[1]))
        {
            pthread_mutex_destroy(&data->forks_mutex[i]);
            i++;
        }
    }
    pthread_mutex_destroy(&data->message);
    pthread_mutex_destroy(&data->dead_m);
    pthread_mutex_destroy(&data->eat_m);
}

int eat_or_dead(t_data *data, t_list *philo)
{
    pthread_mutex_lock(&data->dead_m);
    pthread_mutex_lock(&data->eat_m);
    if ((data->eat == philo->nb_philo) || data->dead == 1)
    {
        pthread_mutex_unlock(&data->dead_m);
        pthread_mutex_unlock(&data->eat_m);
        return (0);
    }
    pthread_mutex_unlock(&data->dead_m);
    pthread_mutex_unlock(&data->eat_m);
    return (1);
}

void meals_eaten(t_data *data, t_list *philo)
{
    pthread_mutex_lock(&data->eat_m);
    if (philo->nb_meals == philo->nb_eat)
        data->eat++;
    pthread_mutex_unlock(&data->eat_m);
}
