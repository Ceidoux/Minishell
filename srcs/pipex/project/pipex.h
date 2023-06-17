/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:30:48 by kali              #+#    #+#             */
/*   Updated: 2023/06/17 16:26:41 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <iso646.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

typedef struct s_tools
{
	int			i;
	int			pipe_fd[2];
	int			file_fd;
	int			pid[2];
	char		**args;
	int			saved_std_out;
	char		*str;
	char		**paths;
	char		**env;
}	t_tools;

int		ft_strlen(char const *str);
int		not_blank(char c, char charset);
int		count_words(char *str, char charset);
char	*put_word(char *str, int start, int end);
char	**ft_split(char *str, char charset);
int		end_of_line(char *str);
char	*real_line(char *line, char *buf, int error);
void	clear_buf(char *buf);
char	*ft_calloc(void);
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlcpy(char *dst, const char *src, int size);
void	ft_bzero(void *s, int n);
void	ft_copy(char *line, char *buf);
char	**ft_split_slash(char *str, char charset);
char	*put_word_slash(char *str, int start, int end);
int		ft_strcmp(char *str1, char *str2);
int		ft_strncmp(char *s1, char *s2, int n);
char	*path_line(char **envp);
void	free_all(t_tools tools);
int		syntax_help(void);
int		non_printable(char *str);
void	no_execution(t_tools tools);
void	print_error(t_tools tools, char *str);
void	absolute_relative_path(t_tools tools);
void	env_path(t_tools tools, char **envp);
char	*remove_path(char *str);
char	*ft_strdup(char *str);
int		end_slash(char *str);
void	free_str_args(t_tools tools);
int		is_slash(char *str);
char	*return_full_line(char *full_line, char *res, int fd);
void	get_next_path(char *full_line, int fd);
void	first_command(t_tools tools, char **argv, char **envp);
void	second_command(t_tools tools, char **argv, char **envp);
void	free_no_path(t_tools tools);
void	ft_putchar(char c, int *len);
void	ft_putstr(char *str, int *len);
void	ft_putnbr(int nbr, int *len);
void	ft_putunsnbr(unsigned int nbr, int *len);
void	ft_putnbr_base(unsigned int nbr, char *base, int *len);
void	ft_putlongnbr_base(long unsigned int nbr, char *base, int *len);
void	ft_putpoint_base(long unsigned int nbr, char *base, int *len);
void	print_format(char *str, int *i, va_list args, int *len);
int		ft_printf(const char *str, ...);

#endif