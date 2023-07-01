/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:00:54 by jleguay           #+#    #+#             */
/*   Updated: 2023/07/01 17:00:55 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void					ft_add_new_line(t_table_of_commands *toc);
static void 				ft_add_command(t_table_of_commands *toc, char *command);
static int					ft_add_input(t_table_of_commands *toc, t_list **tokens);
static int					ft_add_output(t_table_of_commands *toc, t_list **tokens);

t_table_of_commands ft_create_table_of_commands(t_list *tokens)
{
	t_table_of_commands	toc;

	ft_bzero(&toc, sizeof(toc));
	ft_add_new_line(&toc);
	while (tokens)
	{
		if (tokens->type == WORD)
			ft_add_command(&toc, tokens->content);
		else if (tokens->type == OPERATOR && (!ft_strncmp(tokens->content, "<", 2) || !ft_strncmp(tokens->content, "<<", 3)))
		{
			if (ft_add_input(&toc, &tokens))
				return (toc);
		}
		else if (tokens->type == OPERATOR && (!ft_strncmp(tokens->content, ">", 2) || !ft_strncmp(tokens->content, ">>", 3)))
		{
			if(ft_add_output(&toc, &tokens))
				return (toc);
		}
		else
			ft_add_new_line(&toc);
		tokens = tokens->next;
	}
	return (toc);
}

static int	ft_add_input(t_table_of_commands *toc, t_list **tokens)
{
	if (toc->inputs[toc->size - 1])
		close(toc->inputs[toc->size - 1]);	
	if (!ft_strncmp((*tokens)->content, "<", 2))
		toc->inputs[toc->size - 1] = open((*tokens)->next->content, O_RDONLY);
	else 
		toc->inputs[toc->size - 1] = ft_heredoc((*tokens)->next->content);
	if (toc->inputs[toc->size - 1] == -1)
	{
		perror((*tokens)->next->content);
		ft_tocfree(toc);
		return (-1);
	}
	*tokens = (*tokens)->next;
	return (0);
}

static int	ft_add_output(t_table_of_commands *toc, t_list **tokens)
{
	if (toc->outputs[toc->size - 1])
		close(toc->outputs[toc->size - 1]);
	if (!ft_strncmp((*tokens)->content, ">", 2))
		toc->outputs[toc->size - 1] = open((*tokens)->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		toc->outputs[toc->size - 1] = open((*tokens)->next->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (toc->outputs[toc->size - 1] == -1)
	{
		perror((*tokens)->next->content);
		ft_tocfree(toc);
		return (-1);
	}
	*tokens = (*tokens)->next;
	return (0);
}

static void	ft_add_new_line(t_table_of_commands *toc)
{
	t_table_of_commands	new_toc;
	int					line;

	new_toc.size = toc->size + 1;
	new_toc.commands = calloc(new_toc.size, sizeof(*(new_toc.commands)));
	if (!(new_toc.commands))
		exit(EXIT_FAILURE);
	new_toc.inputs = calloc(new_toc.size, sizeof(*(new_toc.inputs)));
	new_toc.outputs = calloc(new_toc.size, sizeof(*(new_toc.outputs)));
	line = -1;
	while (++line < new_toc.size - 1)
	{
		if (toc->commands[line])
			new_toc.commands[line] = ft_strdup(toc->commands[line]);
		new_toc.inputs[line] = toc->inputs[line];
		new_toc.outputs[line] = toc->outputs[line];
	}
	new_toc.inputs[line] = -1;
	new_toc.outputs[line] = -1;
	ft_tocfree(toc);
	*toc = new_toc;
}

static void ft_add_command(t_table_of_commands *toc, char *command)
{
	char	*temp;

	if (!toc->commands[toc->size - 1])
		toc->commands[toc->size - 1] = ft_strdup(command);
	else
	{
		temp = toc->commands[toc->size - 1];
		toc->commands[toc->size - 1] = ft_strjoin(toc->commands[toc->size - 1], " ");
		free(temp);
		temp = toc->commands[toc->size - 1];
		toc->commands[toc->size - 1] = ft_strjoin(toc->commands[toc->size - 1], command);
		free(temp);
	}
}
