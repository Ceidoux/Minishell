#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"

#include <stdlib.h>				// getenv()
#include <fcntl.h> 				// open()
#include <unistd.h> 			// getcwd(), read(), write(), chdir(), unlink()
#include <sys/types.h> 			// read()
#include <sys/uio.h> 			// read()
#include <stdio.h> 				// readline()
#include <readline/readline.h>	// readline()
#include <readline/history.h>	// readline()
#include <signal.h>				// sigaction()
# include <sys/wait.h>			// wait()
# include <stdarg.h>			// va_args

/* nb: use -lreadline when compiling */

extern int	g_exit_status;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_table_of_commands
{
	int		size;
	char	**commands;
	int		*inputs;
	int		*outputs;
}	t_table_of_commands;

typedef struct s_tools
{
	int			i;
	int			**pipe_fd;
	int			file_fd;
	int			*pid;
	char		**args;
	int			saved_std_out;
	char		*str;
	char		**paths;
	int			fd_count;
}	t_tools;

/* builtin directory */
int		ft_cd(char *s);
int		ft_echo(char *s);
int		ft_env(char **envp);
int		ft_exit(char *s);
int		ft_export(t_tools tools, char **envp);
int		ft_pwd(void);
char	**ft_unset(char *s, char **envp);
int		ft_envp_size(char **envp);
char 	**ft_realloc_envp(char **old_envp, size_t new_size);


/* lexer (lexical analyser) directory */
int		ft_check(t_list	*tokens);
int		ft_check_quotes(char *word);
t_list	*ft_lexer(char *s);
void	ft_expand(char **s);
void	ft_unquote(char **s);

/* parser directory */
t_table_of_commands	ft_parser(char *s);
t_table_of_commands ft_create_table_of_commands(t_list *tokens);
int		ft_heredoc(char *delimiter);

/* utils directory */
void	ft_ioclose(t_table_of_commands toc);
void	ft_lstprint(t_list *lst);
void	ft_lstremovelast(t_list **lst, void (*del)(void*));
void	ft_tocprint(t_table_of_commands	toc);
void	ft_tocfree(t_table_of_commands *toc);
char	*ft_remove_endl(char *str);

/* pipex directory */
int		pipex(t_table_of_commands toc, char **envp);
void	init_tools(t_tools *tools, t_table_of_commands toc);
void	command_exec(t_tools tools, t_table_of_commands toc, char **envp);
void	absolute_relative_path(t_tools tools);
void	env_path(t_tools tools);
char	*remove_path(char *str);
int		is_slash(char *str);
int		end_slash(char *str);
void	no_path(t_tools tools);
int		not_blank(char c, char *charset);
int		count_words(char *str, char *charset);
char	*put_word(char *str, int start, int end);
char	**pipex_split(char *str, char *charset);
char	**pipex_split_slash(char *str, char *charset);
char	*put_word_slash(char *str, int start, int end);
void	pipex_putlongnbr_base(long unsigned int nbr, char *base, int *len);
void	pipex_putpoint_base(long unsigned int nbr, char *base, int *len);
void	print_format(char *str, int *i, va_list args, int *len);
int		pipex_printf(const char *str, ...);
int		pipex_strlen(char const *str);
char	*pipex_strjoin(char *s1, char *s2);
void	pipex_putchar(char c, int *len);
void	pipex_putstr(char *str, int *len);
void	pipex_putnbr(int nbr, int *len);
void	pipex_putunsnbr(unsigned int nbr, int *len);
void	pipex_putnbr_base(unsigned int nbr, char *base, int *len);
int		pipex_strncmp(char *s1, char *s2, int n);
char	*pipex_strdup(char *str);
char 	*pipex_putstr2(char *str);
void	free_str_args(t_tools tools);
void	free_main(t_tools *tools);
void	free_path(t_tools tools);
void	free_before(t_tools *tools);
void	free_all(t_tools tools);
void	clean_finish(t_tools tools, t_table_of_commands toc);
void	no_execution(t_tools tools);
void	free_no_path(t_tools tools);
void	failed_open(t_tools tools, char **argv);
void	close_pipes(t_tools tools, t_table_of_commands toc);
int		is_builtin(char *str);
void	builtin_exec(t_tools tools, t_table_of_commands toc, char **envp);
int		ft_strcmp(char *s1, char *s2);
int		ft_strsort(char *s1, char *s2);

#endif