#include "minishell.h"

static int	ft_check_single_operator(char *operator);
static int	ft_check_two_operators(char *operator1, char *operator2);

int	ft_check(t_list	*tokens)
{
	if (!tokens)
		return (1);
	while (tokens)
	{
		if (tokens->type == OPERATOR && !ft_check_single_operator(tokens->content))
			return (0);
		else if (tokens->next && tokens->type == OPERATOR && tokens->next->type == OPERATOR && !ft_check_two_operators(tokens->content, tokens->next->content))
			return (0);
		tokens = tokens->next; 
	}
	return (1);
}

static int	ft_check_single_operator(char *operator)
{
	if (ft_strncmp(operator, "|", 2)
		&& ft_strncmp(operator, ">", 2)
		&& ft_strncmp(operator, "<", 2)
		&& ft_strncmp(operator, ">>", 3)
		&& ft_strncmp(operator, "<<", 3))
	{
		g_exit_status = 127;
		ft_putendl_fd("command not found", 1);
		return(0);
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
	g_exit_status = 127;
	ft_putstr_fd("syntax error near unexpected token \'", 1);
	ft_putstr_fd(operator2, 1);
	ft_putendl_fd("\'", 1);
	return(0);
}
/* Sur les derniers tests, exit_status en cas d'erreur est de 258 (pour un unsigned char ???) */


