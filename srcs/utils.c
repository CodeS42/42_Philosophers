#include "../headers/philo.h"

int     ft_atoi(const char *nptr)
{
    int     i;
    int     result;
    int     sign;

    i = 0;
    result = 0;
    sign = 1;
    while (nptr[i] == 32 || (nptr[i] >= 7 && nptr[i] <= 13))
        i++;
    if (nptr[i] == '-' || nptr[i] == '+')
    {
        if (nptr[i] == '-')
            sign *= -1;
        i++;
    }
    while (nptr[i] >= '0' && nptr[i] <= '9')
    {
        result = result * 10 + nptr[i] - '0';
        i++;
    }
    return (result * sign);
}

t_list  *ft_lstnew(int *id, t_data *data, int argc, char **argv)
{
    t_list  *new;
    struct timeval tv;

    new = malloc(sizeof(t_list));
    if (!new)
        return (error_message("Error\nThread creation failed\n"), NULL);
    new->nb_philo = ft_atoi(argv[1]);
    new->time_to_die = ft_atoi(argv[2]);
    new->time_to_eat = ft_atoi(argv[3]);
    new->time_to_sleep = ft_atoi(argv[4]);
    gettimeofday(&tv, NULL);
    new->start = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    if (argc == 6)
        new->nb_eat = ft_atoi(argv[5]);
    new->nb_meals = 0;
    new->last_meal = new->start;
    new->id = *id;
    new->data = data;
    new->next = NULL;
    return (new);
}

void    *ft_lstadd_back(t_list **lst, t_list *new)
{
    t_list  *tmp;

    if (!new)
        return (NULL);
    if (*lst == NULL)
    {
        *lst = new;
        return (new);
    }
    tmp = *lst;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    return (new);
}

void ft_lstclear(t_list **lst)
{
    t_list *tmp;

    if (lst == NULL)
        return;
    while (*lst)
    {
        tmp = (*lst)->next;
        free(*lst);
        *lst = tmp;
    }
    lst = NULL;
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}
