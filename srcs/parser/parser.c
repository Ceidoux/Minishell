#include "minishell.h"

static t_table_of_commands	ft_create_table_of_commands(t_list *tokens);
static void					ft_add_new_line(t_table_of_commands *toc);
static void 				ft_add_command(t_table_of_commands *toc, char *command);
static int					ft_add_input(t_table_of_commands *toc, t_list **tokens);
static int					ft_add_output(t_table_of_commands *toc, t_list **tokens);

t_table_of_commands	ft_parser(char *s, char **envp)
{
	t_table_of_commands	toc;
	t_list				*tokens;

	tokens = ft_lexer(s, envp);
	ft_lstprint(tokens);
	toc = ft_create_table_of_commands(tokens);
	ft_lstclear(&tokens, &free);
	ft_tocprint(toc);
	return (toc);
}

static t_table_of_commands ft_create_table_of_commands(t_list *tokens)
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
	{
		toc->inputs[toc->size - 1] = open((*tokens)->next->content, O_RDONLY);
		if (toc->inputs[toc->size - 1] == -1)
		{
			perror((*tokens)->next->content);
			ft_tocfree(toc);
			return (-1);
		}
	}
	else 
	{
		/* HEREDOC (<<) */
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
