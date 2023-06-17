NAME        =    pipex

SRCS        =   project/pipex.c project/pipex_utils.c project/pipex_utils_2.c project/pipex_utils_3.c project/pipex_utils_4.c project/pipex_utils_5.c project/split.c project/split_utils.c project/get_next_line.c project/get_next_line_utils.c project/ft_printf.c project/useful_funcs.c

BONUS		=	bonus/pipex_bonus.c bonus/split_bonus.c bonus/get_next_line_bonus.c bonus/get_next_line_utils_bonus.c bonus/pipex_utils_bonus.c bonus/pipex_utils_2_bonus.c bonus/pipex_utils_3_bonus.c bonus/pipex_utils_4_bonus.c bonus/pipex_utils_5_bonus.c bonus/pipex_utils_6_bonus.c bonus/ft_printf_bonus.c bonus/useful_funcs_bonus.c

OBJS        =    ${SRCS:.c=.o}

OBJS_BONUS	=	${BONUS:.c=.o}

CC            =    cc
CFLAGS        =   -Wall -Werror -Wextra

DEPENDANCES	= project/pipex.h  Makefile

DEPANDANCES_BONUS = bonus/pipex_bonus.h Makefile

RM            =    rm -f

%.o: %.c
				${CC} ${CFLAGS} -c $< -o $@

all:            ${NAME}

${NAME}:        ${OBJS} ${DEPENDANCES}
				${CC} ${CFLAGS} -o ${NAME} ${OBJS}

bonus:			${OBJS_BONUS} ${DEPENDANCES_BONUS}
				${CC} ${CFLAGS} -o ${NAME} ${OBJS_BONUS}
clean:
				rm -f $(OBJS)
fclean:            clean
				${RM} ${NAME}

cleanbonus:
				rm -f ${OBJS_BONUS}

fcleanbonus:	cleanbonus
				${RM} ${NAME}

re:                fclean all

rebonus:		fcleanbonus bonus

.PHONY:            all clean fclean re