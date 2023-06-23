NAME        =    pipex

SRCS        =   pipex/project/1_pipex.c pipex/project/2_init.c pipex/project/3_execution.c pipex/project/4_paths.c pipex/project/5_ft_split.c pipex/project/6_ft_split_slash.c pipex/project/7_ft_printf.c pipex/project/8_useful_funcs_1.c pipex/project/9_useful_funcs_2.c pipex/project/10_close_free_1.c pipex/project/11_close_free_2.c

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