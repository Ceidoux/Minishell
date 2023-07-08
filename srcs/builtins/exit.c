/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:16:41 by smestre           #+#    #+#             */
/*   Updated: 2023/07/08 10:05:50 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char *s, t_tools tools, t_cmd toc, char **envp)
{
	unsigned char	n;
	int				sign;

	n = 0;
	sign = 1;
	s += 4;
	while (*s == ' ')
		s++;
	if (!*s)
		return (1);
	if (*s == '+' || *s == '-')
		sign = 44 - *(s++);
	if (!ft_isdigit(*s))
	{
		ft_putendl_fd("exit: numeric argument required", 2);
		if (toc.size == 1)
		{
			tools.pid[tools.i] = fork();
			if (tools.pid[tools.i] == 0)
			{
				ft_pipe_manager(tools, toc);
				clean_finish(tools, toc);
				ft_tocfree(&toc);
				free_all(tools);
				ft_envp_free(envp);
				exit(2);
			}
		}
		return (1);
	}
	while (ft_isdigit(*s))
		n = n * 10 + *(s++) - '0';
	if (*s && *s != ' ')
	{
		ft_putendl_fd("exit: numeric argument required", 2);
		if (toc.size == 1)
		{
			tools.pid[tools.i] = fork();
			if (tools.pid[tools.i] == 0)
			{
				ft_pipe_manager(tools, toc);
				clean_finish(tools, toc);
				ft_tocfree(&toc);
				free_all(tools);
				ft_envp_free(envp);
				exit(2);
			}
		}
		return (1);
	}
	while (*s == ' ')
		s++;
	if (*s)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		if (toc.size == 1)
		{
			tools.pid[tools.i] = fork();
			if (tools.pid[tools.i] == 0)
			{
				ft_pipe_manager(tools, toc);
				clean_finish(tools, toc);
				ft_tocfree(&toc);
				free_all(tools);
				ft_envp_free(envp);
				exit(1);
			}	
		}
		return (0);
	}
	tools.pid[tools.i] = fork();
	if (tools.pid[tools.i] == 0)
	{
		ft_pipe_manager(tools, toc);
		clean_finish(tools, toc);
		ft_tocfree(&toc);
		free_all(tools);
		ft_envp_free(envp);
		exit(n * sign);
	}
	return (1);
}

// A gérer:
// [ok] exit						
// -> If N is not given, the exit status code 
// is that of the last executed command
// [ok] exit [space][space][space] 
// -> renvoie le dernier statut de sortie (identique à exit)
// [ok] exit N						-> returns N (avec N unsigned char)
// [ok] exit -N					-> renvoie la valeur en unsigned char
// [ok] exit 123D					
// -> print error: numeric argument required ET exit avec 255 en return value
// [ok] exit D123					-> idem
// [~] exit 123 123				
// -> print error: too many arguments (MAIS en principe n'exit pas)
// Note: exit ne gère pas l'overflow ! (exit 256 renvoie 0)
