/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:00:48 by jleguay           #+#    #+#             */
/*   Updated: 2023/07/08 10:08:57 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	ft_parser(char *s, char **envp)
{
	t_cmd	toc;
	t_list	*tokens;

	tokens = ft_lexer(s, envp);
	toc = ft_create_table_of_commands(tokens, envp);
	ft_lstclear(&tokens, &free);
	return (toc);
}
