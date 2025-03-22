NAME = philo_bonus

bonus = philo_bonus.c philos_situation_bonus.c \
		start_bonus.c utilis_bonus.c error_bonus.c

flags = -Wall -Wextra -Werror

bobj = ${bonus:.c=.o}

all: ${NAME}

${NAME}: ${bobj}
	cc ${flags} ${bobj} -o ${NAME}

clean:
	rm -f ${bobj}

fclean: clean
	rm -f ${NAME}

re: fclean all

f:
	clear

ra: all clean f