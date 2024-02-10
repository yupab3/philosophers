CC=				cc
CFLAGS=			-Wall -Wextra -Werror
NAME=			philo
FILES=			philosophers ph_atoi ph_init_funcs ph_mutex_funcs ph_putnbr_fd \
				ph_rt_funcs ph_thread_funcs ph_time_funcs ph_util_funcs ph_thread_utils \
				ph_action_funcs ph_action_utils
SRCS=			$(addsuffix .c, $(FILES))
OBJS=			$(SRCS:.c=.o)
HEADER=			philosophers.h

.PHONY: all clean fclean re

all:	$(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o:	%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all
