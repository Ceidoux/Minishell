#include "minishell.h"

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
