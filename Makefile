CC=				cc
CFLAGS=			-Wall -Wextra -Werror
NAME=			philo
NAME_BONUS=		philo_bonus
FILES=			philosophers ph_atoi ph_init_funcs ph_mutex_funcs ph_putnbr_fd \
				ph_rt_funcs ph_thread_funcs ph_time_funcs ph_util_funcs ph_thread_utils
SRC_BONUS=		$(addprefix ./philo_bonus/, $(FILES))
SRCS=			$(addsuffix .c, $(FILES))
SRCS_BONUS=		$(addsuffix _bonus.c, $(SRC_BONUS))
OBJS=			$(SRCS:.c=.o)
OBJS_BONUS=		$(SRCS_BONUS:.c=.o)
HEADER=			philosophers.h
HEADER_BONUS=	./philo_bonus/philosophers_bonus.h

.PHONY: all bonus clean fclean re

all:	$(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -o $@

bonus:	$(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(HEADER_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $@

%.o:	%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

./philo_bonus/%.o:		./philo_bonus/%.c $(HEADER_BONUS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_BONUS)

fclean:	clean
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)

re:	fclean all
