/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:16:25 by smestre           #+#    #+#             */
/*   Updated: 2023/07/05 19:27:22 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	is_slash_n(char *str)
{
	int i;

	i = 0;
	if (str[i] != '-')
		return (0);
	i++;
	if ((!str[i]) || (str[i] && str[i] != 'n'))
		return (0);
	while (str[i] == 'n')
		i++;
	if (str[i] && str[i] != ' ')
		return (0);
	return (i);
} 

void	ft_echo(t_tools tools, char *s, t_cmd_tab toc, char **envp)
{
	t_bool	n_flag;
	int j;
	char *copy;

	copy = NULL;
	ft_pipe_manager(tools, toc);
	n_flag = 0;
	j = 0;
	if (!s[4])
		ft_putchar_fd('\n', 1);
	else
	{
		s += 5;
		j = is_slash_n(s);
		if (j != 0)
		{

			n_flag = 1;
			s += j;
			while (*s && *s == ' ')
				s++;
		}
		copy = ft_strdup(s);
		ft_expand(&copy, envp);
		ft_unquote(&copy);
		if (n_flag)
			printf("%s", copy);
		else
			printf("%s\n", copy);
	}
	free(copy);
	clean_finish(tools, toc);
	ft_tocfree(&toc);
	free_all(tools);
	ft_envp_free(envp);
	exit(0);
}

/*
ATTENTION : echo renvoie les variables de shell, et non seulement les varaibles d'environnement.
-> il ne suffit pas de vérifier dans envp. En principe, aller vérifier du côté de ```set``` qui liste les variables shell (VAR=1 qui enregistre en variable shell versus ```export VAR=1``` qui enregistre comme variable d'environnement)

A gérer :
[**] echo "text"
[**] echo 'text'
[**] echo text
[**] echo "text" 'text' text
[**] echo $MA_VARIABLE
[**] echo '$MA_VAR'
[**] echo "$MA_VAR"
[**] echo $(MA_VAR)
[**] echo $?
[**] echo $$
[**] echo $!				-> PID of last job running in background
[**] echo -n text

[] echo      test
[] echo "     " test

*/