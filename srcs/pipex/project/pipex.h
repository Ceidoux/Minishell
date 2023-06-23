/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:30:48 by kali              #+#    #+#             */
/*   Updated: 2023/06/23 06:04:04 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <iso646.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdarg.h>

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

typedef struct s_table_of_commands
{
	int		size;
	char	**commands;
	int		*inputs;
	int		*outputs;
}	t_table_of_commands;

int		pipex(t_table_of_commands toc);
void	init_tools(t_tools *tools, t_table_of_commands toc);
void	command_exec(t_tools tools, t_table_of_commands toc);
void	absolute_relative_path(t_tools tools);
void	env_path(t_tools tools);
char	*remove_path(char *str);
int		is_slash(char *str);
int		end_slash(char *str);
void	no_path(t_tools tools);
int		not_blank(char c, char charset);
int		count_words(char *str, char charset);
char	*put_word(char *str, int start, int end);
char	**ft_split(char *str, char charset);
char	**ft_split_slash(char *str, char charset);
char	*put_word_slash(char *str, int start, int end);
void	ft_putlongnbr_base(long unsigned int nbr, char *base, int *len);
void	ft_putpoint_base(long unsigned int nbr, char *base, int *len);
void	print_format(char *str, int *i, va_list args, int *len);
int		ft_printf(const char *str, ...);
int		ft_strlen(char const *str);
char	*ft_strjoin(char *s1, char *s2);
void	ft_putchar(char c, int *len);
void	ft_putstr(char *str, int *len);
void	ft_putnbr(int nbr, int *len);
void	ft_putunsnbr(unsigned int nbr, int *len);
void	ft_putnbr_base(unsigned int nbr, char *base, int *len);
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_strdup(char *str);
char 	*ft_putstr2(char *str);
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

#endif