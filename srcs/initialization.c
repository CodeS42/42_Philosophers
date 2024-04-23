#include "../headers/philo.h"

t_data    *init_struct(t_data *data)
{
    data = malloc(sizeof(t_data));
    if (!data)
        return (error_message("Error\nMemory allocation failed\n"), NULL);
    pthread_mutex_init(&data->message, NULL);
    pthread_mutex_init(&data->eat_m, NULL);
    pthread_mutex_init(&data->dead_m, NULL);
    data->dead = 0;
    data->eat = 0;
    data->lst_philos = NULL;
    return (data);
}

int     init_list(t_data *data, int argc, char **argv)
{
    int i;

    i = 1;
    while (i <= ft_atoi(argv[1]))
    {
        if (!ft_lstadd_back(&data->lst_philos, ft_lstnew(&i, data, argc, argv)))
            return (0);
        i++;
    }
    return (1);
}

int     creation_mutex(t_data *data, char **argv)
{
    int i;
    t_list *tmp;

    data->forks_mutex = malloc(ft_atoi(argv[1]) * sizeof(pthread_mutex_t));
    if (!data->forks_mutex)
        return (error_message("Error\nMemory allocation failed\n"), 0);
    i = 0;
    while(i < ft_atoi(argv[1]))
    {
        if (pthread_mutex_init(&data->forks_mutex[i++], NULL) != 0)
            return (error_message("Error\nMutex initialization failed\n"), 0);
    }
    tmp = data->lst_philos;
    i = 0;
    while (tmp)
    {
        if (ft_atoi(argv[1]) > 1)
        	tmp->left_fork = &data->forks_mutex[i];
        if (i == ft_atoi(argv[1]) - 1)
            tmp->right_fork = &data->forks_mutex[0];
        else
            tmp->right_fork = &data->forks_mutex[i++ + 1];
        tmp = tmp->next;
    }
    return (1);
}

int    creation_threads(t_data *data)
{
    t_list *tmp;

    tmp = data->lst_philos;
    while (tmp)
    {
        if (pthread_create(&tmp->philo, NULL, &ft_threads, tmp) != 0)
            return (error_message("Error\nThread creation failed\n"), 0);
        tmp = tmp->next;
    }
    tmp = data->lst_philos; 
    while(tmp)
    {
        pthread_join(tmp->philo, NULL);
        tmp = tmp->next;
    }
    return (1);
}
