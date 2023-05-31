#include "minishell.h"

/* Extrait la variable de l'environnement, size = strlen(param) */
char	*ft_get_var(char *parameter, char **envp, int size)
{
	while (*envp && ft_strncmp(*envp, parameter, size)
		&& (*envp)[size] != '=')						// && ou || ?
		envp++;
	if (!(*envp))
		return (NULL);
	return (*envp + size + 1);
}
