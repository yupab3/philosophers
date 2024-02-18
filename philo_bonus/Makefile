CC=				cc
CFLAGS=			-Wall -Wextra -Werror
NAME_BONUS=		philo_bonus
FILES=			philosophers ph_atoi ph_init_funcs ph_mutex_funcs ph_putnbr_fd \
				ph_rt_funcs ph_thread_funcs ph_time_funcs ph_util_funcs ph_thread_utils \
				ph_action_funcs ph_action_utils
SRCS_BONUS=		$(addsuffix _bonus.c, $(FILES))
OBJS_BONUS=		$(SRCS_BONUS:.c=.o)
HEADER_BONUS=	philosophers_bonus.h

.PHONY: all clean fclean re

all: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(HEADER_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $@

%.o:	%.c $(HEADER_BONUS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS_BONUS)

fclean:	clean
	$(RM) $(NAME_BONUS)

re:	fclean all
