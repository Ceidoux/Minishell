/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_pipex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 11:09:53 by kali              #+#    #+#             */
/*   Updated: 2023/07/05 13:28:22 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*

La fonction principale de Pipex. Apres avoir recu la command table toc, la fonciton
cree autant de child processes que le "size" de toc. On a donc un fork() par commande executee !

*/

int command_type(t_tools tools, t_cmd_tab toc, char ***envp)
{
	if (toc.commands[tools.i] == NULL)
		return(0);
	else
	{
		tools.args = pipex_split(toc.commands[tools.i], " ");
		int i = 0;
		while (tools.args[i])
		{
			printf("args[%d] = %s\n", i, tools.args[i]);
			i++;
		}
		if (ft_strcmp(tools.args[0], "echo"))
		{
			tools.pid[tools.i] = fork();
			if (tools.pid[tools.i] == 0)
				ft_echo(tools, toc.commands[tools.i], toc, *envp);
		}
		else if (is_builtin(tools.args[0], *envp))
		{
			if(builtin_exec(tools, toc, envp) == 1)
				return (1);
		}
		else
		{
			tools.pid[tools.i] = fork();
			if (tools.pid[tools.i] == 0)
				command_exec(tools, toc, *envp);
		}
	}
	return(0);
}
int	pipex(t_cmd_tab toc, char ***envp)
{
	t_tools	tools;

	init_tools(&tools, toc);
	while (tools.i < toc.size)
	{
		if (command_type(tools, toc, envp) == 1)
			return(1);
		(tools.i)++;
	}
	clean_finish(tools, toc);
	return (0);
}

void	ft_pipe_manager(t_tools tools, t_cmd_tab toc)
{
	int j;

	j = 0;
	if (toc.inputs[tools.i] != -1)
		dup2(toc.inputs[tools.i], STDIN_FILENO);
	else if (tools.i > 0)
		dup2(tools.pipe_fd[tools.i - 1][0], STDIN_FILENO);
	if (toc.outputs[tools.i] != -1)
		dup2(toc.outputs[tools.i], STDOUT_FILENO);
	else if (tools.i < toc.size - 1)
		dup2(tools.pipe_fd[tools.i][1], STDOUT_FILENO);
	while (j < toc.size)
	{
		if (tools.pipe_fd[j][0] >= 0)
			close(tools.pipe_fd[j][0]);
		if (tools.pipe_fd[j][1] >= 0)
			close(tools.pipe_fd[j][1]);
		if (toc.inputs[j] >= 0)
			close(toc.inputs[j]);
		if (toc.outputs[j] >= 0)
			close(toc.outputs[j]);
		j++;
	}
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



