/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:00:48 by jleguay           #+#    #+#             */
/*   Updated: 2023/07/01 17:06:56 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_tab	ft_parser(char *s, char **envp)
{
	t_cmd_tab	toc;
	t_list				*tokens;

	tokens = ft_lexer(s, envp);
	// ft_lstprint(tokens);
	toc = ft_create_table_of_commands(tokens);	
	ft_lstclear(&tokens, &free);
	ft_tocprint(toc);
	return (toc);
}
