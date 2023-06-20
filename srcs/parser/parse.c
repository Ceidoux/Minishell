#include "minishell.h"

static char	***ft_create_table_of_commands(t_list *tokens);
static void ft_add_command(char ***toc, char *command);
static void ft_add_input(char ***toc, char *input);
static void ft_add_output(char ***toc, char *output);
static char	***ft_add_new_line(char ***toc);
static int	ft_toc_size(char ***toc);
static void	ft_toc_cpy(char ***dst_toc, char ***src_toc);
static void	ft_toc_free(char ***toc);

char	***ft_parser(char *s, char **envp)
{
	char	***toc;
	t_list	*tokens;

	tokens = ft_lexer(s, envp);
	ft_lstprint(tokens);
	toc = ft_create_table_of_commands(tokens);
	ft_lstclear(&tokens, &free);
	return (toc);
}

static char	***ft_create_table_of_commands(t_list	*tokens)
{
	char	***toc;
	
	toc = ft_calloc(1, sizeof(*toc));
	if (!toc)
		exit(EXIT_FAILURE);
	*toc = ft_calloc(3, sizeof(**toc));
	if (!(*toc))
		exit(EXIT_FAILURE);	
	while (tokens)
	{
		if (tokens->type == OPERATOR && !ft_strncmp(tokens->content, "<", 2))
		{
			tokens = tokens->next;
			ft_add_input(toc, tokens->content);
		}
		else if (tokens->type == OPERATOR && !ft_strncmp(tokens->content, ">", 2))
		{
			tokens = tokens->next;
			ft_add_output(toc, tokens->content);
		}
		else if (tokens->type == WORD)
			ft_add_command(toc, tokens->content);
		else
			toc = ft_add_new_line(toc);
		tokens = tokens->next;
	}
	return (toc);
}

static void ft_add_command(char ***toc, char *command)
{
	int		last_line;
	char	*temp;

	last_line = ft_toc_size(toc) - 1;
	temp = toc[last_line][0];
	toc[last_line][0] = ft_strjoin(toc[last_line][0], " ");
	free(temp);
	temp = toc[last_line][0];
	toc[last_line][0] = ft_strjoin(toc[last_line][0], command);
	free(temp);
}

static void ft_add_input(char ***toc, char *input)
{
	int	last_line;

	last_line = ft_toc_size(toc) - 1;
	toc[last_line][1] = ft_strdup(input);
}

static void ft_add_output(char ***toc, char *output)
{
	int	last_line;

	last_line = ft_toc_size(toc) - 1;
	toc[last_line][2] = ft_strdup(output);	
}

static char	***ft_add_new_line(char ***toc)
{
	char ***new_toc;
	int	toc_size ;
	
	toc_size = ft_toc_size(toc);
	new_toc = calloc((toc_size + 1), sizeof(*new_toc));
	if (!new_toc)
		exit(EXIT_FAILURE);
	ft_toc_cpy(new_toc, toc);
	ft_toc_free(toc);
	new_toc[toc_size] = ft_calloc(3, sizeof(**new_toc));
	if (!(new_toc[toc_size]))
		exit(EXIT_FAILURE);	
	return (new_toc);
}

static void	ft_toc_free(char ***toc)
{
	int	toc_size;
	int	toc_column;

	toc_size = ft_toc_size(toc);
	while (--toc_size)
	{
		toc_column = -1;
		while (++toc_column < 3)
			free(toc[toc_size][toc_column]);
	}
}

static void	ft_toc_cpy(char ***dst_toc, char ***src_toc)
{
	int	toc_size;

	toc_size = ft_toc_size(src_toc);
	while (--toc_size)
	{
		dst_toc[toc_size] = ft_calloc(3, sizeof(**dst_toc));
		if (!(dst_toc[toc_size]))
			exit(EXIT_FAILURE);	
		ft_strlcpy(dst_toc[toc_size][0], src_toc[toc_size][0], ft_strlen(src_toc[toc_size][0]) + 1);
		ft_strlcpy(dst_toc[toc_size][1], src_toc[toc_size][1], ft_strlen(src_toc[toc_size][0]) + 1);
		ft_strlcpy(dst_toc[toc_size][2], src_toc[toc_size][2], ft_strlen(src_toc[toc_size][0]) + 1);
	}
}

static int	ft_toc_size(char ***toc)
{
	int	size;

	if (!toc)
		return (0);
	size = 1;
	while (toc[size][0][0] != '\0')
		size++;
	return (size);
}
