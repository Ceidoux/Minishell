/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:16:25 by smestre           #+#    #+#             */
/*   Updated: 2023/07/08 11:55:53 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	not_quote(char *str, int *i, char c)
{
	(*i)++;
	if (!str[*i] || str[*i] != '-')
		return (0);
	(*i)++;
	if ((!str[*i]) || (str[*i] && str[*i] != 'n'))
		return (0);
	while (str[*i] == 'n')
		(*i)++;
	if (!str[*i] || str[*i] != c)
		return (0);
	(*i)++;
	if (str[*i] && str[*i] != ' ')
		return (0);
	return (1);
}

int	is_slash_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\"')
	{
		if (!not_quote(str, &i, '\"'))
			return (0);
		return (i);
	}
	if (str[i] == '\'')
	{
		if (!not_quote(str, &i, '\''))
			return (0);
		return (i);
	}
	if (str[i] != '-')
		return (0);
	i++;
	if ((!str[i]) || (str[i] && str[i] != 'n'))
		return (0);
	while (str[i] == 'n')
		i++;
	if (str[i] && str[i] != ' ')
		return (0);
	return (i);
}

void	echo_final_free(char *copy, char **envp, t_tools tools, t_cmd toc)
{
	free(copy);
	clean_finish(tools, toc);
	ft_tocfree(&toc);
	free_all(tools);
	ft_envp_free(envp);
	exit(0);
}

void	expand_print(char **copy, char **envp, t_bool n_flag)
{
	ft_expand(copy, envp);
	ft_unquote(copy);
	if (n_flag)
		printf("%s", *copy);
	else
		printf("%s\n", *copy);
}

void	ft_echo(t_tools tools, char *s, t_cmd toc, char **envp)
{
	t_bool	n_flag;
	int		j;
	char	*copy;

	copy = NULL;
	ft_pipe_manager(tools, toc);
	n_flag = 0;
	j = 0;
	if (!s[4])
		ft_putchar_fd('\n', 1);
	else
	{
		s += 5;
		j = is_slash_n(s);
		if (j != 0)
		{
			n_flag = 1;
			s += j;
			while (*s && *s == ' ')
				s++;
		}
		copy = ft_strdup(s);
		expand_print(&copy, envp, n_flag);
	}
	echo_final_free(copy, envp, tools, toc);
}
