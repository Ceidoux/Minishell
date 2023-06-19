#include "minishell.h"

// static int	ft_check_operator(char *operator);

int	ft_check(t_list	*tokens)
{
	if (!tokens)
		return (0);
	return (1);
}

// static int	ft_check_operator(char *operator)
// {
// 	if (ft_strncmp(operator, "|", 2)
// 		&& ft_strncmp(operator, ">", 2)
// 		&& ft_strncmp(operator, "<", 2)
// 		&& ft_strncmp(operator, ">>", 3)
// 		&& ft_strncmp(operator, "<<", 3))
// 		return(ft_putendl_fd("command not found", 1), 127);
// 	return (0);
// }
/* pour bonus
|| !ft_strncmp(operator, "||", 3)
|| !ft_strncmp(operator, "&&", 3)
|| !ft_strncmp(operator, "(", 2)
|| !ft_strncmp(operator, ")", 2)
*/