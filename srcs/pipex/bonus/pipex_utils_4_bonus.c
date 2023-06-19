/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_4_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 19:42:51 by smestre           #+#    #+#             */
/*   Updated: 2023/06/19 14:08:16 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_path(t_tools tools)
{
	perror(tools.str);
	free_str_args(tools);
	free_main(&tools);
	exit(0);
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
		ft_printf("%s: Is a directory\n", tools.str);
		free_str_args(tools);
		free_main(&tools);
		exit(0);
	}
	tools.args[0] = remove_path(tools.args[0]);
	execve(tools.str, tools.args, NULL);
}

void	env_path(t_tools tools, char **envp)
{
	tools.str = path_line(envp);
	if (tools.str == NULL)
		no_path(tools);
	tools.paths = ft_split_slash(tools.str, ':');
	while (tools.paths[tools.j])
	{
		tools.paths[tools.j] = ft_strjoin(tools.paths[(tools.j)],
				tools.args[0]);
		if (tools.paths[tools.j] == NULL)
			return ;
		execve(tools.paths[tools.j], tools.args, NULL);
		(tools.j)++;
	}
	no_execution(tools);
}

char	**ft_split_slash(char *str, char charset)
{
	char	**res;
	int		i;
	int		j;
	int		ancre;

	i = 0;
	j = 0;
	res = malloc(sizeof(char *) * (1 + count_words(str, charset)));
	if (res == NULL)
		return (NULL);
	res[count_words(str, charset)] = NULL;
	while (str[i])
	{
		if (not_blank(str[i], charset))
		{
			ancre = i;
			while (str[i] && not_blank(str[i], charset))
				i++;
			res[j] = put_word_slash(str, ancre, i);
			j++;
		}
		else
			i++;
	}
	return (res);
}

char	*return_full_line(char *full_line, char *res, int fd)
{
	close(fd);
	return (free(res), full_line);
}
