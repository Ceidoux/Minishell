#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# include <stdlib.h>			// getenv()
# include <fcntl.h>				// open()
# include <unistd.h>			// getcwd(), read(), write(), chdir(), unlink()
# include <sys/types.h>			// read()
# include <sys/uio.h>			// read()
# include <stdio.h>				// readline()
# include <readline/readline.h>	// readline()
# include <readline/history.h>	// readline()
# include <signal.h>			// sigaction()
# include <sys/wait.h>			// wait()
# include <stdarg.h>			// va_args

/* nb: use -lreadline when compiling */

extern int	g_exit_status;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_cmd_tab
{
	int		size;
	char	**commands;
	int		*inputs;
	int		*outputs;
}	t_cmd_tab;

typedef struct s_tools
{
	int		i;
	int		**pipe_fd;
	int		file_fd;
	int		*pid;
	char	**args;
	char	*str;
	char	**paths;
	int		fd_count;
}	t_tools;

/* builtin directory */
int		ft_cd(t_tools tools, char **envp);
void	ft_echo(t_tools tools, char *s, t_cmd_tab toc, char **envp);
int		ft_env(char **envp);
int		ft_exit(char *s, int toc_size);
int		ft_pwd(t_tools tools, t_cmd_tab toc);
char	**ft_unset(char *s, char **envp);

/*  Function in Export */
char	**ft_export(t_tools tools, t_cmd_tab toc, char **envp);
int		arg_size(t_tools tools);
void	ft_swap(char **s1, char **s2);
int		env_size(char **envp);
int		has_car(char *str, char c);
int		is_char(char str, char c);
char	**split_two(char *str, int i);
char	**separate_two(char	*str);
char	*modify_var(char *str);
int		ft_len_dif(char *str);
int		plus_equal(char *str);
int		has_invalid_character(char *str);
char	*remove_plus(char *str);
char	**ft_addstr(char **envp, char *str, int envp_size);
void	add_to_env(t_tools *tools, char ***envp, int *size, int *envp_size);
void	print_env(char **export_var, char **envp, int i);
void	child_export(char **export_var, char **envp, int i, int envp_size);
char	**ft_addstr_end(char **envp, char *str, int envp_size);
char	**ft_addstr_plus(char **res, char **envp, char *str, int i);
char	**ft_addstr_replace(char **envp, char *str, int i);


/* End of functions in export*/

/* lexer (lexical analyser) directory */
int		ft_check(t_list	*tokens);
t_list	*ft_lexer(char *s, char **envp);

/* converter directory */
void	ft_expand(char **s, char **envp);
void	ft_unquote(char **s);

/* parser directory */
t_cmd_tab	ft_parser(char *s, char **envp);
t_cmd_tab	ft_create_table_of_commands(t_list *tokens, char **envp);
int		ft_heredoc(char *delimiter, char **envp);

/* utils directory */
int		ft_envp_size(char **envp);
void	ft_envp_free(char **envp);
char	**ft_envp_dup(char **envp);
char	**ft_envp_realloc(char **old_envp, size_t new_size);
char	*ft_getenv(char *var, char **envp);
void	ft_lstprint(t_list *lst);
void	ft_lstremovelast(t_list **lst, void (*del)(void*));
void	ft_tocprint(t_cmd_tab	toc);
void	ft_tocfree(t_cmd_tab *toc);

/* pipex directory */
int		pipex(t_cmd_tab toc, char ***envp);
void	ft_pipe_manager(t_tools tools, t_cmd_tab toc);
void	init_tools(t_tools *tools, t_cmd_tab toc);
void	command_exec(t_tools tools, t_cmd_tab toc, char **envp);
void	absolute_relative_path(t_tools tools);
void	env_path(t_tools tools, char **envp);
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
char	*pipex_putstr2(char *str);
void	free_str_args(t_tools tools);
void	free_main(t_tools *tools);
void	free_path(t_tools tools);
void	free_before(t_tools *tools);
void	free_all(t_tools tools);
void	clean_finish(t_tools tools, t_cmd_tab toc);
void	no_execution(t_tools tools);
void	free_no_path(t_tools tools);
void	failed_open(t_tools tools, char **argv);
void	close_pipes(t_tools tools, t_cmd_tab toc);
int		is_builtin(char *str, char **envp);
int		builtin_exec(t_tools tools, t_cmd_tab toc, char ***envp);
int		ft_strcmp(char *s1, char *s2);
int		ft_strsort(char *s1, char *s2);
char	*get_path(char **envp, char *str);
int		ft_len_before_equal(char *str);
int		env_var_exists(char **envp, char *str);
int		error_pipex_printf(const char *str, ...);
void	error_pipex_putpoint_base(long unsigned int nbr, char *base, int *len);
void	error_pipex_putlongnbr_base(long unsigned int nbr, char *base, int *len);
void	error_pipex_putchar(char c, int *len);
void	error_pipex_putstr(char *str, int *len);
void	error_pipex_putnbr(int nbr, int *len);
void	error_pipex_putunsnbr(unsigned int nbr, int *len);
void	error_pipex_putnbr_base(unsigned int nbr, char *base, int *len);

#endif