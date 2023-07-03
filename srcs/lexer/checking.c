/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:01:09 by jleguay           #+#    #+#             */
/*   Updated: 2023/07/01 17:08:25 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_single_operator(char *operator);
static int	ft_check_two_operators(char *operator1, char *operator2);
static int	ft_check_last_operator(char *operator);

int	ft_check(t_list	*tokens)
{
	if (!tokens)
		return (1);
	if (tokens->type == OPERATOR && !ft_strncmp(tokens->content, "|", 2))
	{
		g_exit_status = 258;
		ft_putendl_fd("syntax error near unexpected token '|'", 1);
		return (0);
	}
	while (tokens)
	{
		if (tokens->type == OPERATOR && !ft_check_single_operator(tokens->content))
			return (0);
		else if (tokens->next && tokens->type == OPERATOR && tokens->next->type == OPERATOR && !ft_check_two_operators(tokens->content, tokens->next->content))
			return (0);
		else if (!tokens->next && tokens->type == OPERATOR && !ft_check_last_operator(tokens->content))
			return (0);
		// else if (tokens->type == WORD)
		// {
		// 	if (!ft_check_quotes(tokens->content))
		// 		return (0);
		// 	ft_unquote(&(tokens->content));
		// }
		tokens = tokens->next;
	}
	return (1);
}

static int	ft_check_last_operator(char *operator)
{
	if (!ft_strncmp(operator, "|", 2)
		|| !ft_strncmp(operator, "<", 2)
		|| !ft_strncmp(operator, ">", 2)
		|| !ft_strncmp(operator, ">>", 3)
		|| !ft_strncmp(operator, "<<", 3)
		|| !ft_strncmp(operator, "<>", 3))
	{
		g_exit_status = 258;
		ft_putendl_fd("syntax error near unexpected token 'newline'", 1);
		return (0);
	}
	return (1);
}

static int	ft_check_single_operator(char *operator)
{
	if (ft_strncmp(operator, "|", 2)
		&& ft_strncmp(operator, ">", 2)
		&& ft_strncmp(operator, "<", 2)
		&& ft_strncmp(operator, ">>", 3)
		&& ft_strncmp(operator, "<<", 3)
		&& ft_strncmp(operator, "<>", 3))
	{
		g_exit_status = 258;
		ft_putstr_fd("parse error near \'", 1);
		ft_putstr_fd(operator, 1);
		ft_putendl_fd("\'", 1);
		return (0);
	}
	return (1);
}
/* pour bonus
|| !ft_strncmp(operator, "||", 3)
|| !ft_strncmp(operator, "&&", 3)
|| !ft_strncmp(operator, "(", 2)
|| !ft_strncmp(operator, ")", 2)
*/

static int	ft_check_two_operators(char *operator1, char *operator2)
{
	(void) operator1;
	g_exit_status = 258;
	ft_putstr_fd("syntax error near unexpected token \'", 1);
	ft_putstr_fd(operator2, 1);
	ft_putendl_fd("\'", 1);
	return (0);
}
/* exit_status en cas d'erreur est de 258  */
