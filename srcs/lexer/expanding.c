#include "minishell.h"

static char	*ft_expand_var(char *s, int idx);

/* expansion des variables unquoted
nb: char** car on passe l'adresse d'un str */
void	ft_expand(char **s)
{
	int		idx;
	t_bool	simple_quote;
	t_bool	double_quote;

	idx = 0;
	simple_quote = FALSE;
	double_quote = FALSE;
	while ((*s)[idx])
	{
		if ((*s)[idx] == '$' && simple_quote == FALSE)
		{
			*s = ft_expand_var(*s, idx + 1);
			continue;
		}
		else if ((*s)[idx] == '\"' && simple_quote == FALSE)
			double_quote = (double_quote == FALSE);
		else if ((*s)[idx] == '\'' && double_quote == FALSE)
			simple_quote = (simple_quote == FALSE);
		idx++;
	}
}

static char	*ft_expand_var(char *s, int idx)
{
	char	*var_name;
	char	*var;
	char	*new_s;
	int		len;

	len = 0;
	while (ft_isalnum(s[len + idx]) || s[len + idx] == '_')
		len++;
	if (!len)
		return (s);
	var_name = ft_substr(s, idx, len);
	var = getenv(var_name);
	free(var_name);
	new_s = malloc((ft_strlen(s) - len + ft_strlen(var)) * sizeof(*new_s));
	if (!new_s)
		return (NULL);
	ft_strlcpy(new_s, s, idx);
	if (var)
		ft_strlcpy(new_s + idx - 1, var, ft_strlen(var) + 1);
	ft_strlcpy(new_s + idx - 1 + ft_strlen(var), s + idx + len, ft_strlen(s) - (idx + len) + 1);
	free(s);
	return (new_s);
}

/*
A gerer:
[**] $VAR_DEFINIE
[**] $VAR_NON_DEFINIE	-> echo $VAR_UNDEFINIED Output: (nothing)
[**] $ blabla 			--> e.g. echo $ qs ($ immediatement suivi d'un espace) Output: $ qs ($ conserve)
[**] blabla$			->
[**] "$USER"			--> jle
[**] '$USER'			--> $USER
[**] $?					--> dernier output !!

N'a pas a etre gere:
[-] $0 $1 $2...		--> verifier l'output sur bash
[-] $1USER			--> Output:USER ($1 est traite comme un variable)
[-] $#				--> affiche le nombre d'arguments (?)
[-] $*
[-] $!
[-] $$
[-] $-
*/
