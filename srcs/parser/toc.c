/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:00:54 by jleguay           #+#    #+#             */
/*   Updated: 2023/07/08 14:34:58 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_add_command(t_cmd *toc, char *command);
static int	ft_add_input(t_cmd *toc, t_list **tokens, char **envp);
static int	ft_add_output(t_cmd *toc, t_list **tokens, char **envp);

t_cmd	ft_create_table_of_commands(t_list *tok, char **envp)
{
	t_cmd	toc;

	ft_memset(&toc, 0, sizeof(toc));
	ft_add_new_line(&toc);
	while (tok)
	{
		if (tok->type == WORD)
			ft_add_command(&toc, tok->content);
		else if ((!ft_strncmp(tok->content, "<", 2)
				|| !ft_strncmp(tok->content, "<<", 3)))
		{
			if (ft_add_input(&toc, &tok, envp))
				return (toc);
		}
		else if ((!ft_strncmp(tok->content, ">", 2) || !ft_strncmp(tok->content,
					">>", 3) || !ft_strncmp(tok->content, "<>", 3)))
		{
			if (ft_add_output(&toc, &tok, envp))
				return (toc);
		}
		else
			ft_add_new_line(&toc);
		tok = tok->next;
	}
	return (toc);
}

static int	ft_add_input(t_cmd *toc, t_list **tokens, char **envp)
{
	t_bool	is_quoted;

	if (toc->inputs[toc->size - 1] >= 0)
		close(toc->inputs[toc->size - 1]);
	if (!ft_strncmp((*tokens)->content, "<", 2))
	{
		ft_expand(&(*tokens)->next->content, envp);
		ft_unquote(&(*tokens)->next->content);
		toc->inputs[toc->size - 1] = open((*tokens)->next->content, O_RDONLY);
	}
	else
	{
		is_quoted = ft_is_quoted((*tokens)->next->content);
		ft_unquote(&(*tokens)->next->content);
		toc->inputs[toc->size - 1] = ft_heredoc((*tokens)->next->content, envp,
				is_quoted);
	}
	if (toc->inputs[toc->size - 1] == -1)
	{
		if (errno)
			perror((*tokens)->next->content);
		return (ft_tocfree(toc), -1);
	}
	*tokens = (*tokens)->next;
	return (0);
}

static int	ft_add_output(t_cmd *toc, t_list **tokens, char **envp)
{
	ft_expand(&(*tokens)->next->content, envp);
	ft_unquote(&(*tokens)->next->content);
	if (toc->outputs[toc->size - 1] >= 0
		&& ft_strncmp((*tokens)->content, "<>", 3))
		close(toc->outputs[toc->size - 1]);
	if (!ft_strncmp((*tokens)->content, ">", 2))
		toc->outputs[toc->size - 1] = open((*tokens)->next->content,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (!ft_strncmp((*tokens)->content, "<>", 3))
		close(open((*tokens)->next->content,
				O_WRONLY | O_CREAT | O_APPEND, 0644));
	else
		toc->outputs[toc->size - 1] = open((*tokens)->next->content,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (toc->outputs[toc->size - 1] == -1
		&& ft_strncmp((*tokens)->content, "<>", 3))
	{
		perror((*tokens)->next->content);
		ft_tocfree(toc);
		return (-1);
	}
	*tokens = (*tokens)->next;
	return (0);
}

static void	ft_add_command(t_cmd *toc, char *command)
{
	char	*temp;

	if (!toc->commands[toc->size - 1])
		toc->commands[toc->size - 1] = ft_strdup(command);
	else
	{
		temp = toc->commands[toc->size - 1];
		toc->commands[toc->size - 1] = ft_strjoin(toc->commands[toc->size - 1],
				" ");
		free(temp);
		temp = toc->commands[toc->size - 1];
		toc->commands[toc->size - 1] = ft_strjoin(toc->commands[toc->size - 1],
				command);
		free(temp);
	}
}
