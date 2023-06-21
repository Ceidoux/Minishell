#include "minishell.h"

static t_table_of_commands	ft_create_table_of_commands(t_list *tokens);
static void					ft_add_new_line(t_table_of_commands *toc);
static void					ft_toc_tablecpy(char ***dst_table, char ***src_table, int size);
static void 				ft_add_command(t_table_of_commands *toc, char *command);
static void					ft_add_input(t_table_of_commands *toc, t_list **tokens);
static void					ft_add_output(t_table_of_commands *toc, t_list **tokens);

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
		else if (tokens->type == OPERATOR && !ft_strncmp(tokens->content, "<", 2))
			ft_add_input(&toc, &tokens);
		else if (tokens->type == OPERATOR && !ft_strncmp(tokens->content, ">", 2))
			ft_add_output(&toc, &tokens);
		else
			ft_add_new_line(&toc);
		tokens = tokens->next;
	}
	return (toc);
}

static void	ft_add_input(t_table_of_commands *toc, t_list **tokens)
{
	*tokens = (*tokens)->next;
	if (toc->table[toc->size - 1][1])
		free(toc->table[toc->size - 1][1]);
	toc->table[toc->size - 1][1] = ft_strdup((*tokens)->content);
}

static void	ft_add_output(t_table_of_commands *toc, t_list **tokens)
{
	*tokens = (*tokens)->next;
	if (toc->table[toc->size - 1][2])
		free(toc->table[toc->size - 1][2]);
	toc->table[toc->size - 1][2] = ft_strdup((*tokens)->content);
}

static void	ft_add_new_line(t_table_of_commands *toc)
{
	char ***new_table;

	new_table = malloc((toc->size + 1) * sizeof(*new_table));
	if (!new_table)
		exit(EXIT_FAILURE);
	ft_toc_tablecpy(new_table, toc->table, toc->size);
	ft_tocfree(toc);
	new_table[toc->size] = ft_calloc(3, sizeof(**new_table));
	if (!(new_table[toc->size]))
		exit(EXIT_FAILURE);
	toc->table = new_table;
	toc->size++;
}

static void	ft_toc_tablecpy(char ***dst_table, char ***src_table, int size)
{
	while (--size >= 0)
	{
		dst_table[size] = ft_calloc(3, sizeof(**dst_table));
		if (!(dst_table[size]))
			exit(EXIT_FAILURE);
		if (src_table[size][0])
			dst_table[size][0] = ft_strdup(src_table[size][0]);
		if (src_table[size][1])
			dst_table[size][1] = ft_strdup(src_table[size][1]);
		if (src_table[size][2])
			dst_table[size][2] = ft_strdup(src_table[size][2]);
	}
}

static void ft_add_command(t_table_of_commands *toc, char *command)
{
	char	*temp;

	if (!toc->table[toc->size - 1][0])
		toc->table[toc->size - 1][0] = ft_strdup(command);
	else
	{
		temp = toc->table[toc->size - 1][0];
		toc->table[toc->size - 1][0] = ft_strjoin(toc->table[toc->size - 1][0], " ");
		free(temp);
		temp = toc->table[toc->size - 1][0];
		toc->table[toc->size - 1][0] = ft_strjoin(toc->table[toc->size - 1][0], command);
		free(temp);
	}
}
