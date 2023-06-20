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

extern unsigned char	g_exit_status;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

/* builtin directory */
int		ft_cd(char *s, char ** envp);
int		ft_echo(char *s, char **envp);
int		ft_env(char **envp);
int		ft_exit(char *s);
int		ft_export(char *s, char **envp);
int		ft_pwd(void);
int		ft_unset(char *s, char **envp);

/* lexer (lexical analyser) directory */
int		ft_check(t_list	*tokens);
t_list	*ft_lexer(char *s, char **envp);
void	ft_expand(char **s, char **envp);
void	ft_unquote(char **s);

/* parser directory */
char	***ft_parser(char *s, char **envp);

/* utils directory */
void	ft_lstprint(t_list *lst);
void	ft_lstremovelast(t_list **lst, void (*del)(void*));
char	*ft_get_var(char *parameter, char **envp);
char	*ft_remove_endl(char *str);

#endif