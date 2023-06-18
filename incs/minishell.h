#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"

#include <fcntl.h> 				// open()
#include <unistd.h> 			// getcwd(), read(), chdir()
#include <sys/types.h> 			// read()
#include <sys/uio.h> 			// read()
#include <stdio.h> 				// readline()
#include <readline/readline.h>	// readline()
#include <readline/history.h>	// readline()

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

/* in builtin directory */
int		ft_cd(char *s, char ** envp);
int		ft_echo(char *s, char **envp);
int		ft_env(char **envp);
int		ft_exit(char *s, int exit_status);
int		ft_export(char *s, char **envp);
int		ft_pwd(void);
int		ft_unset(char *s, char **envp);

/* environment.c */
char	*ft_get_var(char *parameter, char **envp);

/* utils.c */
char	*ft_remove_endl(char *str);
void	ft_lstprint(t_list *lst);

/* parse.c */
t_list	*ft_parse(char *line);
void	ft_expand(t_list *tokens, char **envp);

#endif