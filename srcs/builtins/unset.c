#include "minishell.h"

int	ft_unset(char *s, char **envp)
{
	char	**new_envp;
	int		new_size;

	if (getenv(s))
	{
		new_size = ft_
		
	}
	return (0);
}

/*
A gérer :
[**] unset VAR_QUI_EXISTE		-> supprime la variable de l'environnement
[**] unset VAR_QUI_N'EXISTE_PAS	-> ne fait rien
[**] unset VAR1 VAR2			-> ceci va unset les 2 variables
[**] unset VAR1 VAR2 VAR3 VAR4	-> ceci va unset les 4 variables
[**] unset						-> unset: not enough arguments

nota : utiliser ft_split !!!
*/