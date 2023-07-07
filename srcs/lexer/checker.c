/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:01:09 by jleguay           #+#    #+#             */
/*   Updated: 2023/07/05 18:03:11 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_single_operator(char *operator);
static int	ft_check_two_operators(char *operator1, char *operator2);
static int	ft_check_last_operator(char *operator);
static int	ft_check_quotes(char *word);

int	ft_check(t_list	*tokens)
{
	if (!tokens)
		return (1);
	if (tokens->type == OPERATOR && !ft_strncmp(tokens->content, "|", 2))
	{
		g_exit_status = 258;
		ft_putendl_fd("syntax error near unexpected token `|'", 1);
		return (0);
	}
	while (tokens)
	{
		if (tokens->type == OPERATOR && !ft_check_single_operator(tokens->content))
			return (0);
		else if (tokens->next && tokens->type == OPERATOR
			&& tokens->next->type == OPERATOR
			&& !ft_check_two_operators(tokens->content, tokens->next->content))
			return (0);
		else if (!tokens->next && tokens->type == OPERATOR
			&& !ft_check_last_operator(tokens->content))
			return (0);
		else if (tokens->type == WORD && !ft_check_quotes(tokens->content))
				return (0);
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
		ft_putendl_fd("syntax error near unexpected token `newline'", 1);
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
		ft_putstr_fd("parse error near `", 1);
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
	if (!ft_strncmp(operator1, "|", 2) && (!ft_strncmp(operator2, "<", 2)
		|| !ft_strncmp(operator2, ">", 2) || !ft_strncmp(operator2, "<<", 3)
		|| !ft_strncmp(operator2, ">>", 3)))
		return (1);
	g_exit_status = 258;
	ft_putstr_fd("syntax error near unexpected token `", 1);
	ft_putstr_fd(operator2, 1);
	ft_putendl_fd("\'", 1);
	return (0);
}
/* exit_status en cas d'erreur est de 258  */

static int	ft_check_quotes(char *word)
{
	int		idx;
	t_bool	simple_quote;
	t_bool	double_quote;

	idx = -1;
	simple_quote = FALSE;
	double_quote = FALSE;
	while (word[++idx])
	{
		if (word[idx] == '\"' && simple_quote == FALSE)
			double_quote = (double_quote == FALSE);
		else if (word[idx] == '\'' && double_quote == FALSE)
			simple_quote = (simple_quote == FALSE);
	}
	if (double_quote == FALSE && simple_quote == FALSE)
		return (1);
	g_exit_status = 258;
	if (double_quote == TRUE)
		ft_putendl_fd("syntax error: expected \" not found", 1);
	else if (simple_quote == TRUE)
		ft_putendl_fd("syntax error: expected \' not found", 1);
	return (0);
}
