NAME        =    pipex

SRCS        =   project/1_pipex.c project/2_init.c project/3_execution.c project/4_paths.c project/5_ft_split.c project/6_ft_split_slash.c project/7_ft_printf.c project/8_get_next_line.c project/9_get_next_line_utils.c project/10_useful_funcs_1.c project/11_useful_funcs_2.c project/12_close_free_1.c project/13_close_free_2.c

OBJS        =    ${SRCS:.c=.o}

CC            =    cc
CFLAGS        =   -Wall -Werror -Wextra

DEPENDANCES	= project/pipex.h  Makefile

RM            =    rm -f

%.o: %.c
				${CC} ${CFLAGS} -c $< -o $@

all:            ${NAME}

${NAME}:        ${OBJS} ${DEPENDANCES}
				${CC} ${CFLAGS} -o ${NAME} ${OBJS}

clean:
				rm -f $(OBJS)
fclean:            clean
				${RM} ${NAME}

re:                fclean all

.PHONY:            all clean fclean re