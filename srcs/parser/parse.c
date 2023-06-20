#include "minishell.h"

static char	***ft_create_toc(t_list	*tokens);
static char	***ft_add_command_line(char ***toc, t_list *tokens);
static int	ft_toc_size(char ***toc);
static void	ft_toc_cpy(char ***dst_toc, char ***src_toc);
static void	ft_toc_free(char ***toc);

char	***ft_parser(char *s, char **envp)
{
	char	***toc;
	t_list	*tokens;

	tokens = ft_lexer(s, envp);
	toc = ft_create_toc(tokens);
	ft_lstprint(tokens);
	ft_lstclear(&tokens, &free);
	return (toc);
}

static char	***ft_create_toc(t_list	*tokens)
{
	char	***toc;
	
	toc = ft_calloc(1, sizeof(*toc));
	if (!toc)
		exit(FAILURE);
	*toc = ft_calloc(3, sizeof(**toc));
	if (!(*toc))
		exit(FAILURE);	
	while (tokens)
	{
		if (tokens->type == OPERATOR && !ft_strncmp(tokens->type, "<", 2))
			ft_add_input(toc, tokens);
		else if (tokens->type == OPERATOR && !ft_strncmp(tokens->type, ">", 2))
			ft_add_output(toc, tokens);
		else if (tokens->type == WORD)
			ft_add_command(toc, tokens);
		else
			toc = ft_add_command_line(toc, tokens);
		tokens = tokens->next;
	}
	return (toc);
}

static void ft_add_command(char ***toc, t_list tokens)
{
	int	last_line;

	last_line = ft_toc_size(toc) - 1;
	toc[last_line][1] = ft_strdup(tokens->content);
}

static void ft_add_input(char ***toc, t_list tokens)
{
	int	last_line;

	last_line = ft_toc_size(toc) - 1;
	toc[last_line][1] = ft_strdup(tokens->content);
}

static void ft_add_output(char ***toc, t_list tokens)
{
	int	last_line;

	last_line = ft_toc_size(toc) - 1;
	toc[last_line][2] = ft_strdup(tokens->content);	
}

static char	***ft_add_command_line(char ***toc, t_list *tokens)
{
	char **new_toc;
	int	toc_size ;
	
	toc_size = ft_toc_size(toc);
	new_toc = calloc((toc_size + 1), sizeof(*new_toc));
	if (!new_toc)
		exit(EXIT_FAILURE);
	ft_toc_cpy(new_toc, toc);
	ft_toc_free(toc);
	new_toc[toc_size] = ft_calloc(3, sizeof(**new_toc));
	if (!(new_toc[toc_size]))
		exit(FAILURE);	
	return (new_toc);
}

static void	ft_toc_free(char ***toc)
{
	int	toc_size;
	int	toc_column;

	toc_size = ft_toc_size(src_toc);
	while (--toc_size)
	{
		toc_column = -1;
		while (++toc_colum < 3)
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
			exit(FAILURE);	
		ft_strlcpy(dst_toc[toc_size][0], src_toc[toc_size][0]);
		ft_strlcpy(dst_toc[toc_size][1], src_toc[toc_size][1]);
		ft_strlcpy(dst_toc[toc_size][2], src_toc[toc_size][2]);
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
