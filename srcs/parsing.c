#include "../headers/philo.h"

void error_message(char *msg)
{
    write(STDERR_FILENO, msg, ft_strlen(msg));
}

int valid_args(int argc, char **argv)
{
    int i;
    int j;

    if (argc < 5)
        return (error_message("Error\nToo few arguments\n"), 0);
    else if (argc > 6)
        return (error_message("Error\nToo many arguments\n"), 0);
    i = 1;
    while (argv[i])
    {
        j = 0;
        while (argv[i][j])
        {
            if (argv[i][j] < '0' || argv[i][j] > '9')
                return (error_message("Error\nInvalid arguments\n"), 0);
            j++;
        }
        i++;
    }
    if (ft_atoi(argv[1]) < 1)
        return (error_message("Error\nThere must be at least one philosopher\n"), 0);
    return (1);
}
