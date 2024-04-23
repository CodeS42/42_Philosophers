#include "../headers/philo.h"

long  current_time(t_list *philo)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000) - philo->start);
}

static void    end_of_simulation(t_data *data, char **argv)
{
    if (data)
    {
        if (data->lst_philos)
            ft_lstclear(&data->lst_philos);
        destroy_mutexes(data, argv);
        if (data->forks_mutex)
            free(data->forks_mutex);
        free(data);
    }
}

int     main(int argc, char **argv)
{
    t_data *data;

    if (!valid_args(argc, argv))
        return (1);
    data = NULL;
    data = init_struct(data);
    if (!data)
        return (1);
    if (!init_list(data, argc, argv))
        return (end_of_simulation(data, argv), 1);
    if (!creation_mutex(data, argv))
        return (end_of_simulation(data, argv), 1);
    if (!creation_threads(data))
        return (end_of_simulation(data, argv), 1);
    end_of_simulation(data, argv);
    return(0);
}
