/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 19:39:35 by smestre           #+#    #+#             */
/*   Updated: 2023/06/16 18:43:20 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	syntax_help(void)
{
	ft_printf("Error : Wrong Number of arguments.\n");
	ft_printf("Syntax should be as follows : ");
	ft_printf("FILE1 CMD1  CMD2 ....... FILE2\n");
	return (1);
}

int	non_printable(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 0 && str[i] <= 32) || str[i] == 127)
			i++;
		else
			return (0);
	}
	return (1);
}

void	init_tools(t_tools *tools, int argc)
{
	tools->i = 0;
	tools->pipe_fd = malloc(sizeof(int *) * (argc - 1));
	if (tools->pipe_fd == NULL)
		return ;
	tools->pipe_fd[argc - 2] = NULL;
	while (tools->i < argc - 2)
	{
		tools->pipe_fd[tools->i] = malloc(sizeof(int) * 2);
		if (tools->pipe_fd[tools->i] == NULL)
		{
			free_before(tools);
			return ;
		}
		pipe(tools->pipe_fd[tools->i]);
		(tools->i)++;
	}
	tools->pid = malloc(sizeof(int) * (argc - 2));
	if (tools->pid == NULL)
		return ;
	tools->i = 0;
}

int	is_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	free_str_args(t_tools tools)
{
	int	i;

	i = 0;
	while (tools.args[i])
	{
		free(tools.args[i]);
		i++;
	}
	free(tools.args);
	free(tools.str);
}
