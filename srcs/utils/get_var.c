#include "minishell.h"

/* /!\ La fonction getenv (autorisée) fait exactement la même chose ! */

/* Extrait la variable de l'environnement */
char	*ft_get_var(char *parameter, char **envp)
{
	int size;

	size = ft_strlen(parameter);
	while (*envp && (ft_strncmp(*envp, parameter, size)
		|| (*envp)[size] != '='))
		envp++;
	if (!(*envp))
		return (NULL);
	return (*envp + size + 1);
}
