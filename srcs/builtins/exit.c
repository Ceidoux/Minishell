/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:16:41 by smestre           #+#    #+#             */
/*   Updated: 2023/07/08 11:29:26 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_exit(t_tools tools, t_cmd toc, char **envp, int ex)
{
	ft_pipe_manager(tools, toc);
	clean_finish(tools, toc);
	ft_tocfree(&toc);
	free_all(tools);
	ft_envp_free(envp);
	exit(ex);
}

void	not_digit_case(t_tools tools, t_cmd toc, char **envp)
{
	ft_putendl_fd("exit: numeric argument required", 2);
	tools.pid[tools.i] = fork();
	if (tools.pid[tools.i] == 0)
		clean_exit(tools, toc, envp, 2);
}

void	many_arguments(t_tools tools, t_cmd toc, char **envp)
{
	ft_putendl_fd("exit: too many arguments", 2);
	tools.pid[tools.i] = fork();
	if (tools.pid[tools.i] == 0)
		clean_exit(tools, toc, envp, 1);
}

int	ft_exit(char *s, t_tools tools, t_cmd toc, char **envp)
{
	unsigned char	n;
	int				sign;

	n = 0;
	sign = 1;
	while (*s == ' ')
		s++;
	if (!*s)
		return (1);
	if (*s == '+' || *s == '-')
		sign = 44 - *(s++);
	if (!ft_isdigit(*s))
		return (not_digit_case(tools, toc, envp), 1);
	while (ft_isdigit(*s))
		n = n * 10 + *(s++) - '0';
	if (*s && *s != ' ')
		return (not_digit_case(tools, toc, envp), 1);
	while (*s == ' ')
		s++;
	if (*s)
		return (many_arguments(tools, toc, envp), 0);
	tools.pid[tools.i] = fork();
	if (tools.pid[tools.i] == 0)
		clean_exit(tools, toc, envp, n * sign);
	return (1);
}
