#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct      s_list
{
    int             id;
    pthread_t       philo;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    int             nb_meals;
    long            last_meal;
    int             nb_philo;
    int             time_to_die;
    int             time_to_sleep;
    int             time_to_eat;
    int             nb_eat; 
    long            start;
    struct s_data   *data;
    struct s_list   *next;
}                   t_list;

typedef struct      s_data
{
    pthread_mutex_t message;
    pthread_mutex_t dead_m;
    pthread_mutex_t eat_m;
    pthread_mutex_t *forks_mutex;
    int             dead;
    int             eat;
    t_list          *lst_philos;
}                   t_data;

t_data  *init_struct(t_data *data);
int     init_list(t_data *data, int argc, char **argv);
int     creation_mutex(t_data *data, char **argv);
int     creation_threads(t_data *data);

long    current_time(t_list *philo);

void    print_message(long time, int id, char *msg, t_data *data);
void    philo_death(t_list *philo, t_data *data);
void    destroy_mutexes(t_data *data,char **argv);
int     eat_or_dead(t_data *data, t_list *philo);
void    meals_eaten(t_data *data, t_list *philo);

int     valid_args(int argc, char **argv);
void    error_message(char *msg);

void    *ft_threads(void *arg);

int     ft_atoi(const char *nptr);
void    ft_lstclear(t_list **lst);
void    *ft_lstadd_back(t_list **lst, t_list *new);
t_list  *ft_lstnew(int *id, t_data *data, int argc, char **argv);
int     ft_strlen(char *str);

#endif