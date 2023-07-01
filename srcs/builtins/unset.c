#include "minishell.h"

static char	**ft_unset_my_var(char *varname, char **old_envp);

char	**ft_unset(char *s, char **envp)
{
	char	**var_tab;
	int		idx;

	var_tab = ft_split(s, ' ');
	idx = 0;
	while (var_tab[++idx])
		envp = ft_unset_my_var(var_tab[idx], envp);
	while (--idx >= 0)
		free(var_tab[idx]);
	free(var_tab);
	return (envp);
}

static char	**ft_unset_my_var(char *varname, char **old_envp)
{
	char	**new_envp;
	int		old_size;
	int		offset;

	if (env_var_exists(old_envp, varname))
	{
		old_size = ft_envp_size(old_envp);
		new_envp = malloc((old_size) * sizeof(*new_envp));
		if (!new_envp)
			exit(EXIT_FAILURE);
		new_envp[--old_size] = NULL;
		offset = 1;
		while (--old_size >= 0)
		{
			if (!ft_strncmp(varname, old_envp[old_size], ft_strlen(varname)) && old_envp[old_size][ft_strlen(varname)] == '=')
				offset = 0;
			else
				new_envp[old_size - offset] = ft_strdup(old_envp[old_size]);
		}
		ft_envp_free(old_envp);
		return (new_envp);
	}
	else
		return (old_envp);
}


/*


A gérer :
[**] unset VAR_QUI_EXISTE		-> supprime la variable de l'environnement
[**] unset VAR_QUI_N'EXISTE_PAS	-> ne fait rien
[**] unset VAR1 VAR2			-> ceci va unset les 2 variables
[**] unset VAR1 VAR2 VAR3 VAR4	-> ceci va unset les 4 variables
[**] unset						-> unset: not enough arguments --> FAUX: pas sur bash --posix

nota : utiliser ft_split !!!
*/