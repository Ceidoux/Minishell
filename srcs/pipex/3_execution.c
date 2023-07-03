/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_execution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 20:06:29 by kali              #+#    #+#             */
/*   Updated: 2023/07/03 14:29:06 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include <string.h>

/*  Voici la partie qui execute les commandes de pipex.
    
    La fonction command_exec() verifie bien les Fds obtenus par 
    le parser, afin de bien rediriger chaque input et output.

    les fonctions absolute_relative_path() et env_path() sont
    quant a elles les fonctions chargees d'executer les commandes, en
    fonciton de si un chemin est specifie ou si on prends les commandes
    de la variable d'environnement PATH respectivements.

*/

void	command_exec(t_tools tools, t_cmd_tab toc, char **envp)
{
	int	j;

	ft_expand(tools.args, envp);
	ft_unquote(tools.args);
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
	close(tools.saved_std_out);
	if (is_slash(tools.args[0]))
		absolute_relative_path(tools);
	else
		env_path(tools, envp);
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
	g_exit_status = execve(tools.str, tools.args, NULL);
	perror(tools.str);
	no_execution(tools);
}

int	ft_len_before_equal(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

int	env_var_exists(char **envp, char *str)
{
	int	i;

	i = 0;
	while(envp[i])
	{
		if (((size_t)ft_len_before_equal(envp[i]) == ft_strlen(str) && ft_strncmp(envp[i], str, ft_len_before_equal(envp[i])) == 0))
			return (1);
		i++;
	}
	return (0);
}


char	*get_path(char **envp, char *str)
{
	int i;
	char	*res;

	i = 0;
	while(envp[i])
	{
		if ((ft_strlen(envp[i]) == ft_strlen(str) && ft_strncmp(envp[i], str, ft_strlen(str)) == 0) || ft_strncmp(envp[i], str, 5) == 0)
		{
			res = ft_strdup(envp[i]);
			return (res);
		}
		i++;
	}
	return (NULL);
}

void	env_path(t_tools tools, char **envp)
{
	// tools.str = getenv("PATH");
	tools.str = get_path(envp, "PATH=");
	if (tools.str == NULL)
		no_path(tools);
	tools.paths = pipex_split_slash(tools.str, ":");
	// for (int i = 0; tools.args[i]; i++)
	// 	fprintf(stderr,"ARG %d: %s\n", i, tools.args[i]);
	tools.i = 0;
	while (tools.paths[tools.i])
	{
		tools.paths[tools.i] = ft_strjoin(tools.paths[(tools.i)],
				tools.args[0]);
		if (tools.paths[tools.i] == NULL)
			return ;
		g_exit_status = execve(tools.paths[tools.i], tools.args, NULL);
		(tools.i)++;
	}
	// perror(tools.args[0]);
	no_execution(tools);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
} 

int	ft_strsort(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s2[i] - s1[i]);
		i++;
	}
	return (0);
} 

int	is_builtin(char *str)
{
	if (ft_strcmp(str, "cd") || ft_strcmp(str, "echo")
		|| ft_strcmp(str, "env") || ft_strcmp(str, "exit")
		|| ft_strcmp(str, "export") || ft_strcmp(str, "pwd") || ft_strcmp(str, "unset"))
		return (1);
	return (0);
}

void	builtin_exec(t_tools tools, t_cmd_tab toc, char ***envp)
{
	ft_expand(tools.args, *envp);
	ft_unquote(tools.args);
	if (ft_strcmp(tools.args[0], "cd"))
		ft_cd(tools, *envp);
	else if (ft_strcmp(tools.args[0], "echo"))
		ft_echo(tools, toc.commands[tools.i], toc, *envp);
	else if (ft_strcmp(tools.args[0], "env"))
		ft_env(*envp);
	else if (ft_strcmp(tools.args[0], "exit"))
		ft_exit(toc.commands[tools.i]);
	else if (ft_strcmp(tools.args[0], "export"))
		*envp = ft_export(tools, *envp);
	else if (ft_strcmp(tools.args[0], "pwd"))
		ft_pwd(tools);
	else if (ft_strcmp(tools.args[0], "unset"))
		*envp = ft_unset(toc.commands[tools.i], *envp);
}
