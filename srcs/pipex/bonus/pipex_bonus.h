/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:30:48 by kali              #+#    #+#             */
/*   Updated: 2023/06/19 15:16:26 by smestre          ###   ########.fr       */
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
# include "../../../libft/libft.h"

typedef struct s_tools
{
	int			i;
	int			j;
	int			**pipe_fd;
	int			file_fd;
	int			*pid;
	char		**args;
	int			saved_std_out;
	char		*str;
	char		**paths;
	int			nombre_fds;
	char		buf[200];
}	t_tools;

void	first_command(t_tools tools, int argc, char *argv[], char **envp);
void	middle_commands(t_tools tools, int argc, char *argv, char **envp);
void	last_command(t_tools tools, char *argv, char *file, char **envp);
// int		ft_strlen(char const *str);
int		not_blank(char c, char charset);
int		count_words(char *str, char charset);
char	*put_word(char *str, int start, int end);
// char	**ft_split(char *str, char charset);
char	**ft_split_slash(char *str, char charset);
char	*put_word_slash(char *str, int start, int end);
void	free_main(t_tools *tools);
int		syntax_help(void);
int		non_printable(char *str);
void	init_tools(t_tools *tools, int argc);
int		is_slash(char *str);
void	free_str_args(t_tools tools);
char	*remove_path(char *str);
void	no_execution(t_tools tools);
int		end_slash(char *str);
// char	*ft_strdup(char *str);
void	free_main(t_tools *tools);
void	absolute_relative_path(t_tools tools);
void	env_path(t_tools tools, char **envp);
void	free_all(t_tools tools);
char	*finding_path(void);
char	*free_finding_path(char *full_line, char *res, int fd);
char	*ft_trim(char *str);
int		ft_strcmp(char *str1, char *str2);
int		non_printable(char *str);
void	failed_open(t_tools tools, char **argv);
void	close_rest_1(t_tools tools, int first_fd);
void	clean_finish(t_tools tools, int argc);
void	last_part(t_tools tools, char **argv, char **envp);
void	first_part(t_tools tools, int argc, char **argv, char **envp);
char	*return_full_line(char *full_line, char *res, int fd);
void	get_next_path(char *full_line, int fd);
void	free_before(t_tools *tools);
// int		ft_strncmp(char *s1, char *s2, int n);
char	*path_line(char **envp);
void	no_path(t_tools tools);
void	free_no_path(t_tools tools);
// char	*ft_strjoin(char *s1, char *s2);
// int		ft_strlcpy(char *dst, const char *src, int size);
// void	ft_bzero(void *s, int n);
void	ft_copy(char *line, char *buf);
int		end_of_line(char *str);
char	*real_line(char *line, char *buf, int error);
void	clear_buf(char *buf);
// char	*ft_calloc(void);
char	*get_next_line(int fd);
void	ft_putchar(char c, int *len);
void	ft_putstr(char *str, int *len);
void	ft_putnbr(int nbr, int *len);
void	ft_putunsnbr(unsigned int nbr, int *len);
void	ft_putnbr_base(unsigned int nbr, char *base, int *len);
void	ft_putlongnbr_base(long unsigned int nbr, char *base, int *len);
void	ft_putpoint_base(long unsigned int nbr, char *base, int *len);
void	print_format(char *str, int *i, va_list args, int *len);
int		ft_printf(const char *str, ...);
char	*ft_strjoin_space(char *s1, char *s2);

#endif