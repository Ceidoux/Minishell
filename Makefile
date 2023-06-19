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

# Mandatory: Sources, Objects
SRCS	:= main.c \
		   builtins/cd.c \
		   builtins/echo.c \
		   builtins/env.c \
		   builtins/exit.c \
		   builtins/export.c \
		   builtins/pwd.c \
		   builtins/unset.c \
		   parsing/parse.c \
		   parsing/expand.c \
		   parsing/unquote.c \
		   utils/ft_lstprint.c \
		   utils/ft_lstremovelast.c \
		   utils/get_var.c \
		   utils/remove_endl.c
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

$(NAME): $(if $(filter bonus, $(MAKECMDGOALS)), $(OBJS_BONUS), $(OBJS)) | _libft
	@echo $(BLUE)[BUILDING] $@$(NOCOLOR)
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@
	@echo $(GREEN)[OK] $@$(NOCOLOR)

$(OBJSDIR)/%.o: $(if $(filter bonus, $(MAKECMDGOALS)), $(SRCSDIR_BONUS)/%.c, $(SRCSDIR)/%.c) | $(OBJSSUBDIR)
	$(CC) $(CFLAGS) -c $< -I$(INCSDIR) -o $@

#========== LIBRARIES AND DIRECTORIES ============================================
$(OBJSSUBDIR):
	-mkdir -p $@

.PHONY= _libft
_libft:
#	@echo $(BLUE)[BUILDING] $@$(NOCOLOR)
	@$(MAKE) -C $(LIBFTDIR)
#	@echo $(GREEN)[OK] $@$(NOCOLOR)

#========== MISCELLANEOUS ========================================================
.PHONY: nof
nof: CFLAGS := -MMD -MP
nof: all

.PHONY: debug
debug: CC := gcc
debug: LDFLAGS += -g -fsanitize=address
debug: CFLAGS += -g
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