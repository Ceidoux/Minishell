/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_execution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 20:06:29 by kali              #+#    #+#             */
/*   Updated: 2023/06/23 10:31:50 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"

/*  Voici la partie qui execute les commandes de pipex.
    
    La fonction command_exec() verifie bien les Fds obtenus par 
    le parser, afin de bien rediriger chaque input et output.

    les fonctions absolute_relative_path() et env_path() sont
    quant a elles les fonctions chargees d'executer les commandes, en
    fonciton de si un chemin est specifie ou si on prends les commandes
    de la variable d'environnement PATH respectivements.

*/

void	command_exec(t_tools tools, t_table_of_commands toc)
{
	int	j;

	j = 0;
	tools.saved_std_out = dup(1);
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

		close(tools.pipe_fd[j][0]);
		close(tools.pipe_fd[j][1]);
		close(toc.inputs[j]);
		close(toc.outputs[j]);
		j++;
	}
	close(tools.saved_std_out);
	tools.args = ft_split(toc.commands[tools.i], ' ');
	if (is_slash(toc.commands[tools.i]))
		absolute_relative_path(tools);
	else
		env_path(tools);
}

void	absolute_relative_path(t_tools tools)
{
	tools.str = ft_strdup(tools.args[0]);
	if (tools.str == NULL)
		return ;
	if (access(tools.str, F_OK) == -1)
		free_path(tools);
	else if (access(tools.str, X_OK) == -1)
	{
		perror(tools.str);
		free_str_args(tools);
		free_main(&tools);
		exit(0);
	}
	else if (end_slash(tools.str))
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		pipex_printf("%s: Is a directory\n", tools.str);
		free_str_args(tools);
		free_main(&tools);
		exit(0);
	}
	tools.args[0] = remove_path(tools.args[0]);
	execve(tools.str, tools.args, NULL);
	perror(tools.str);
	no_execution(tools);
}

void	env_path(t_tools tools)
{
	tools.str = getenv("PATH");
	if (tools.str == NULL)
		no_path(tools);
	tools.paths = pipex_split_slash(tools.str, ':');
	// for (int i = 0; tools.args[i]; i++)
	// 	fprintf(stderr,"ARG %d: %s\n", i, tools.args[i]);
	tools.i = 0;
	while (tools.paths[tools.i])
	{
		tools.paths[tools.i] = ft_strjoin(tools.paths[(tools.i)],
				tools.args[0]);
		if (tools.paths[tools.i] == NULL)
			return ;
		execve(tools.paths[tools.i], tools.args, NULL);
		(tools.i)++;
	}
	perror(tools.args[0]);
	no_execution(tools);
}