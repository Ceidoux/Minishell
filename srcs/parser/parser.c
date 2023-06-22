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
