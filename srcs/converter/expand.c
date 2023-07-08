/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:01:16 by jleguay           #+#    #+#             */
/*   Updated: 2023/07/08 10:06:54 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_expand_var(char **s, int idx, char **envp);
static int	ft_expand_exit_status(char **s, int idx);
static void	ft_remove_dollar_sign(char **s, int idx);

/* expansion des variables unquoted
nb: char** car on passe l'adresse d'un str */
void	ft_expand(char **s, char **envp)
{
	int		i;
	t_bool	squote;
	t_bool	dquote;

	i = 0;
	squote = FALSE;
	dquote = FALSE;
	while ((*s)[i])
	{
		if ((*s)[i] == '$' && squote == FALSE)
		{
			if (dquote == FALSE && ((*s)[i + 1] == '\'' || (*s)[i + 1] == '\"'))
				ft_remove_dollar_sign(s, i + 1);
			else if ((*s)[i + 1] == '?')
				i += ft_expand_exit_status(s, i + 1);
			else
				i += ft_expand_var(s, i + 1, envp);
			continue ;
		}
		else if ((*s)[i] == '\"' && squote == FALSE)
			dquote = (dquote == FALSE);
		else if ((*s)[i] == '\'' && dquote == FALSE)
			squote = (squote == FALSE);
		i++;
	}
}

static void	ft_remove_dollar_sign(char **s, int idx)
{
	char	*new_s;
	char	*old_s;
	int		old_size;
	
	old_size = ft_strlen(*s);
	new_s = malloc(old_size * sizeof(*new_s));
	if (!new_s)
		exit(EXIT_FAILURE);
	ft_strlcpy(new_s, *s, idx);
	ft_strlcpy(new_s + idx - 1, *s + idx, old_size - idx + 1);
	old_s = *s;
	*s = new_s;
	free(old_s);
}

static int	ft_expand_exit_status(char **s, int idx)
{
	char	*exit_status;
	int		exit_status_length;
	char	*new_s;
	char	*old_s;

	exit_status = ft_itoa(g_exit_status);
	exit_status_length = ft_strlen(exit_status);
	new_s = malloc((ft_strlen(*s) - 1 + exit_status_length) * sizeof(*new_s));
	if (!new_s)
		exit(EXIT_FAILURE);
	ft_strlcpy(new_s, *s, idx);
	if (exit_status && *exit_status)
		ft_strlcpy(new_s + idx - 1, exit_status, exit_status_length + 1);
	ft_strlcpy(new_s + idx - 1 + exit_status_length, *s + idx + 1,
		ft_strlen(*s) - idx);
	free(exit_status);
	old_s = *s;
	*s = new_s;
	free(old_s);
	return (exit_status_length);
}

static int	ft_expand_var(char **s, int idx, char **envp)
{
	char	*var_name;
	char	*var;
	char	*new_s;
	char	*old_s;
	int		len;

	len = 0;
	while (ft_isalnum((*s)[len + idx]) || (*s)[len + idx] == '_')
		len++;
	if (!len)
		return (1);
	var_name = ft_substr(*s, idx, len);
	var = ft_getenv(var_name, envp);
	free(var_name);
	new_s = malloc((ft_strlen(*s) - len + ft_strlen(var)) * sizeof(*new_s));
	if (!new_s)
		exit(EXIT_FAILURE);
	ft_strlcpy(new_s, *s, idx);
	if (var)
		ft_strlcpy(new_s + idx - 1, var, ft_strlen(var) + 1);
	ft_strlcpy(new_s + idx - 1 + ft_strlen(var), *s + idx + len,
		ft_strlen(*s) - (idx + len) + 1);
	old_s = *s;
	*s = new_s;
	return (free(old_s), ft_strlen(var));
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
