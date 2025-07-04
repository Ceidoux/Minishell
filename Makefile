NAME	:= minishell

# Compiler, Linker and Flags
CC		:= cc
CFLAGS	+= -Wall -Werror -Wextra
CFLAGS 	+= -MMD -MP
LDFLAGS +=

# Libraries
LIBFT		:= libft.a
LIBS		+= -L$(LIBFTDIR) -lft	# libft
LIBS		+= -lreadline

# Directories
SRCSDIR 		:= srcs
SRCSDIR_BONUS	:= srcs_bonus
OBJSDIR			:= objs
OBJSSUBDIR 		:= $(subst $(SRCSDIR), $(OBJSDIR), $(shell find $(SRCSDIR) -type d))
INCSDIR			:= incs
LIBFTDIR		:= libft
# PIPEXDIR		:= $(SRCSDIR)/pipex

# Mandatory: Sources, Objects
SRCS	:= main.c \
		   builtins/cd.c \
		   builtins/echo.c \
		   builtins/env.c \
		   builtins/exit.c \
		   builtins/export.c \
		   builtins/export2.c \
		   builtins/export3.c \
		   builtins/export4.c \
		   builtins/export5.c \
		   builtins/pwd.c \
		   builtins/unset.c \
		   converter/expand.c \
		   converter/unquote.c \
		   lexer/checker.c \
		   lexer/lexer.c \
		   parser/heredoc.c \
		   parser/parser.c \
		   parser/toc.c \
		   parser/toc2.c \
		   utils/ft_envp_utils.c \
		   utils/ft_lstprint.c \
		   utils/ft_lstremovelast.c \
		   utils/ft_tocfree.c \
		   utils/ft_tocprint.c \
		   pipex/1_pipex.c \
		   pipex/2_init.c \
		   pipex/3_execution.c \
		   pipex/4_paths.c \
		   pipex/5_ft_split.c \
		   pipex/6_ft_split_slash.c \
		   pipex/7_ft_printf.c \
		   pipex/8_useful_funcs_1.c \
		   pipex/9_useful_funcs_2.c \
		   pipex/10_close_free_1.c \
		   pipex/11_close_free_2.c \
		   pipex/error_printf.c \
		   pipex/pipex_utils.c \
		   pipex/pipex_utils2.c \
		   pipex/pipex_utils3.c \
		   pipex/error_printf2.c


OBJS 	:= $(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))

# Bonus: Sources, Objects
#SRCS_BONUS	:= $(addprefix $(SRCSDIR_BONUS)/, \
			   main_bonus.c)
#OBJS_BONUS	:= $(patsubst %.c,$(OBJSDIR)/%.o,$(notdir $(SRCS_BONUS)))

# Dependencies
DEPS		:= $(OBJS:.o=.d) #$(OBJS_BONUS:.o=.d)

# Headers
# INCS		 := minishell.h
# INCS_BONUS := minishell.h

# Colors
RED		:=	"\033[0;31m"
GREEN	:=	"\033[0;32m"
BLUE	:=	"\033[0;34m"
NOCOLOR	:=	"\033[0m"

#---------------------------------------------------------------------------------
# DO NOT EDIT BELOW THIS LINE
#---------------------------------------------------------------------------------

.PHONY: all
all: $(NAME)

.PHONY: bonus
bonus: all

$(NAME): $(if $(filter bonus, $(MAKECMDGOALS)), $(OBJS_BONUS), $(OBJS)) | _libft #_pipex
	@echo $(BLUE)[BUILDING] $@$(NOCOLOR)
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@
	@echo $(GREEN)[OK] $@$(NOCOLOR)

$(OBJSDIR)/%.o: $(if $(filter bonus, $(MAKECMDGOALS)), $(SRCSDIR_BONUS)/%.c, $(SRCSDIR)/%.c) | $(OBJSSUBDIR)
	$(CC) $(CFLAGS) -c $< -I$(INCSDIR) -o $@

#========== LIBRARIES AND DIRECTORIES ============================================
$(OBJSSUBDIR):
	-mkdir -p $@

.PHONY: _libft
_libft:
	@echo $(BLUE)[BUILDING] $@$(NOCOLOR)
	@$(MAKE) -C $(LIBFTDIR)
	@echo $(GREEN)[OK] $@$(NOCOLOR)

# .PHONY: _pipex
# _pipex:
# 	@echo $(BLUE)[BUILDING] $@$(NOCOLOR)
# 	@$(MAKE) -C $(PIPEXDIR)
# 	@echo $(GREEN)[OK] $@$(NOCOLOR)

#========== MISCELLANEOUS ========================================================
.PHONY: nof
nof: CFLAGS := -MMD -MP
nof: all

.PHONY: debug
debug: CC := gcc
#debug: LDFLAGS += -g -fsanitize=address
debug: CFLAGS += -g3
debug: re

.PHONY: sanitize
sanitize: CC := gcc
sanitize: CFLAGS += -g -fsanitize=address
sanitize: LDFLAGS += -g -fsanitize=address
sanitize: re

.PHONY: clean
clean:
	$(MAKE) clean -C $(LIBFTDIR)
	-rm -rf $(OBJSDIR)

.PHONY: fclean
fclean: clean
	-rm -f $(LIBFTDIR)/$(LIBFT)
	-rm -f $(NAME)

.PHONY: re
re: fclean all

-include $(DEPS)