/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_pipex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 11:09:53 by kali              #+#    #+#             */
/*   Updated: 2023/07/01 16:48:40 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*

La fonction principale de Pipex. Apres avoir recu la command table toc, la fonciton
cree autant de child processes que le "size" de toc. On a donc un fork() par commande executee !

*/

int	pipex(t_cmd_tab toc, char ***envp)
{
	t_tools	tools;

	init_tools(&tools, toc);
	while (tools.i < toc.size)
	{
		tools.args = ft_split(toc.commands[tools.i], ' ');
		if (is_builtin(tools.args[0]))
			builtin_exec(tools, toc, envp);
		else
		{
			tools.pid[tools.i] = fork();
			if (tools.pid[tools.i] == 0)
				command_exec(tools, toc, *envp);
		}
		(tools.i)++;
	}
	clean_finish(tools, toc);
	return (0);
}



/**se tout seul et a configurer manuellement pour simuler une arrivee de T.O.C dans Pipex
	sans passer par minishell !
	
int main(void)
{
	t_cmd_tab toc;

	toc.commands = malloc(sizeof(char*) * 5);
	toc.commands[0] = ft_putstr2("grep S");
	toc.commands[1] = ft_putstr2("grep e");
	toc.commands[2] = ft_putstr2("uniq");
	toc.commands[3] = ft_putstr2("wc -c");
	toc.inputs = malloc(sizeof(int) * 4);
	toc.inputs[0] = open("file1.txt", O_RDONLY, 0644);
	toc.inputs[1] = -1;
	toc.inputs[2] = -1;
	toc.inputs[3] = -1;
	toc.outputs = malloc(sizeof(int) * 4);
	toc.outputs[0] = -1;
	toc.outputs[1] = -1;
	toc.outputs[2] = -1;
	toc.outputs[3] = open("testo", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	toc.size = 4;
	pipex(toc);
	return (0);
}

*/



