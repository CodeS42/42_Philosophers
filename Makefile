SRCS =	srcs/main.c \
		srcs/utils.c \
		srcs/initialization.c \
		srcs/mutexes.c \
		srcs/threads.c \
		srcs/parsing.c \

OBJS = $(SRCS:.c=.o)

INCLUDES = headers
NAME = philo

.c.o	:
	cc -Wall -Wextra -Werror -I $(INCLUDES) -c $< -o $(<:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	cc $(OBJS) -o $(NAME)

clean :
	rm -f $(OBJS) 
	
fclean : clean
	rm -f $(NAME)
	
re : fclean all

.PHONY : all clean fclean re
