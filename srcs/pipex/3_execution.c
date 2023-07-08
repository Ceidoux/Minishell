/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_execution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 20:06:29 by kali              #+#    #+#             */
/*   Updated: 2023/07/08 10:57:07 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include <string.h>

void	command_exec(t_tools tools, t_cmd toc, char **envp)
{
	int	j;

	j = 0;
	while (tools.args[j])
	{
		ft_expand(&tools.args[j], envp);
		ft_unquote(&tools.args[j]);
		j++;
	}
	j = 0;
	ft_pipe_manager(tools, toc);
	if (is_slash(tools.args[0]))
		absolute_relative_path(tools, envp, toc);
	else
		env_path(tools, envp, toc);
}

void	free_n_exit(t_tools tools, t_cmd toc, char **envp, int ex)
{
	ft_tocfree(&toc);
	ft_envp_free(envp);
	free_main(&tools);
	free_all(tools);
	exit(ex);
}

void	free_and_exit(t_tools tools, t_cmd toc, char **envp, int ex)
{
	perror(tools.str);
	ft_tocfree(&toc);
	ft_envp_free(envp);
	free_main(&tools);
	free_all(tools);
	exit(ex);
}

void	absolute_relative_path(t_tools tools, char **envp, t_cmd toc)
{
	tools.str = ft_strdup(tools.args[0]);
	if (tools.str == NULL)
		return ;
	if (access(tools.str, F_OK) == -1)
		free_and_exit(tools, toc, envp, 127);
	else if (access(tools.str, X_OK) == -1)
		free_and_exit(tools, toc, envp, 126);
	else if (end_slash(tools.str))
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		error_pipex_printf("%s: Is a directory\n", tools.str);
		ft_tocfree(&toc);
		ft_envp_free(envp);
		free_main(&tools);
		free_all(tools);
		exit(126);
	}
	tools.args[0] = remove_path(tools.args[0]);
	execve(tools.str, tools.args, envp);
	perror(tools.str);
	ft_tocfree(&toc);
	ft_envp_free(envp);
	no_execution(tools);
}

int	ft_len_before_equal(char *str)
{
	int	i;

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
	while (envp[i])
	{
		if (((size_t)ft_len_before_equal(envp[i]) == ft_strlen(str)
				&& ft_strncmp(envp[i], str, ft_len_before_equal(envp[i])) == 0))
			return (1);
		i++;
	}
	return (0);
}

char	*get_path(char **envp, char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (envp[i])
	{
		if ((ft_strlen(envp[i]) == ft_strlen(str)
				&& ft_strncmp(envp[i], str, ft_strlen(str)) == 0)
			|| ft_strncmp(envp[i], str, 5) == 0)
		{
			res = ft_strdup(envp[i]);
			return (res);
		}
		i++;
	}
	return (NULL);
}

char	*remove_beginning(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		i++;
	res = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (res == NULL)
		return (NULL);
	while (str[i])
		res[j++] = str[i++];
	res[j] = 0;
	free(str);
	return (res);
}

void	env_path(t_tools tools, char **envp, t_cmd toc)
{
	tools.str = get_path(envp, "PATH=");
	if (tools.str == NULL || tools.str[5] == 0)
	{
		ft_tocfree(&toc);
		ft_envp_free(envp);
		no_path(tools);
	}
	tools.paths = pipex_split_slash(tools.str, ":");
	if (tools.paths[0])
		tools.paths[0] = remove_beginning(tools.paths[0]);
	tools.i = 0;
	while (tools.paths[tools.i])
	{
		tools.paths[tools.i] = pipex_strjoin(tools.paths[(tools.i)],
				tools.args[0]);
		if (tools.paths[tools.i] == NULL)
			return ;
		execve(tools.paths[tools.i], tools.args, envp);
		(tools.i)++;
	}
	ft_tocfree(&toc);
	ft_envp_free(envp);
	no_execution(tools);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

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
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s2[i] - s1[i]);
		i++;
	}
	return (0);
} 

int	is_builtin(char *str, char **envp)
{
	char	*copy;

	copy = NULL;
	copy = ft_strdup(str);
	ft_expand(&copy, envp);
	ft_unquote(&copy);
	if (ft_strcmp(copy, "cd") || ft_strcmp(copy, "echo")
		|| ft_strcmp(copy, "env") || ft_strcmp(copy, "exit")
		|| ft_strcmp(copy, "export") || ft_strcmp(copy, "pwd")
		|| ft_strcmp(copy, "unset"))
	{	
		free(copy);
		return (1);
	}
	free(copy);
	return (0);
}

int	builtin_exec(t_tools tools, t_cmd toc, char ***envp)
{
	tools.j = -1;
	while (tools.args[++(tools.j)])
	{
		ft_expand(&tools.args[tools.j], *envp);
		ft_unquote(&tools.args[tools.j]);
	}
	if (ft_strcmp(tools.args[0], "cd"))
		return (ft_cd(tools, *envp, toc));
	else if (ft_strcmp(tools.args[0], "env"))
		return (ft_env(tools, toc, *envp));
	else if (ft_strcmp(tools.args[0], "exit"))
	{
		ft_expand(&toc.commands[tools.i], *envp);
		ft_unquote(&toc.commands[tools.i]);
		return (ft_exit(toc.commands[tools.i] + 4, tools, toc, *envp)
			& (toc.size == 1));
	}
	else if (ft_strcmp(tools.args[0], "export"))
		return (*envp = ft_export(tools, toc, *envp), 0);
	else if (ft_strcmp(tools.args[0], "pwd"))
		return (ft_pwd(tools, toc, *envp));
	else if (ft_strcmp(tools.args[0], "unset"))
		return (*envp = ft_unset(toc.commands[tools.i], *envp), 0);
	return (0);
}
