/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 17:13:41 by jleguay           #+#    #+#             */
/*   Updated: 2023/07/02 17:14:33 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_has_equal_sign(char *s);

int	ft_env(char **envp)
{
	while (*envp)
		if (ft_has_equal_sign(*envp))
			ft_putendl_fd(*(envp++), 1);
	return (0);
}

static int	ft_has_equal_sign(char *s)
{
	while (*s)
		if (*s == '=')
			return (1);
	return (0);
}

/*
A gérer (pas d'option, pas d'argument):
[ok] env
[*]	si export zzz	-> env n'affiche pas zzz (alors que export le fait)
*/
