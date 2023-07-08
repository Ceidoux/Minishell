/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:16:49 by smestre           #+#    #+#             */
/*   Updated: 2023/07/08 10:05:50 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

// char	*modify_var(char *str)  /*  Fonction  qui 
//retire tous les ' et les " presents dans la variable"*/
// {
// 	char	**res;
// 	int		i;
// 	i = 0;
// 	if (has_car(str, '\'') != -1 || has_car(str, '\"') != -1)
// 	{
// 		res = pipex_split(str, "'\"");
// 		i++;
// 		while (res[i])
// 		{
// 			res[0] = ft_strjoin(res[0], res[i]);
// 			i++;
// 		}
// 		i = 1;
// 		while(res[i])
// 		{
// 			free(res[i]);
// 			i++;
// 		}
// 		str = ft_strdup(res[0]);
// 		free(res[0]);
// 		free(res);
// 		i = 0;
// 	}
// 	// if (has_car(str, '=') != -1)
// 	// {
// 		// res = pipex_split(str, "=");
// 	// 	// res[0] = ft_strjoin(res[0], "=\"");
// 	// 	// i++;
// 	// 	// while(res[i])
// 	// 	// {
// 	// 	// 	if (flag == 1)
// 	// 	// 		res[0] = ft_strjoin(res[0], "=");
// 	// 	// 	else
// 	// 	// 		flag = 1;
// 	// 	// 	res[0] = ft_strjoin(res[0], res[i]);
// 	// 	// 	i++;
// 	// 	// }
// 	// 	// res[0] = ft_strjoin(res[0], "\"");
// 	// 	res = separate_two(str);
// 	// 	res[0] = ft_strjoin(res[0], "=\"");
// 	// 	i = 1;
// 	// 	while (res[i])
// 	// 	{
// 	// 		res[0] = ft_strjoin(res[0], res[i]);
// 	// 		i++;
// 	// 	}
// 	// 	res[0] = ft_strjoin(res[0], "\"");
// 	// 	i = 1;
// 	// 	while(res[i])
// 	// 	{
// 	// 		free(res[i]);
// 	// 		i++;
// 	// 	}
// 	// 	str = ft_strdup(res[0]);
// 	// 	free(res[0]);
// 	// 	free(res);
// 	// }
// 	return (str);
// }

// fonction principale. Affiche env par 
//ordre alphabetique si aucun paramtere, sinon
// export les variables selon des regles precises.

char	**ft_export(t_tools tools, t_cmd toc, char **envp)
{
	int		i;
	int		size;
	int		envp_size;
	char	**export_var;

	i = 0;
	export_var = NULL;
	size = arg_size(tools);
	envp_size = env_size(envp);
	if (size == 1)
	{
		tools.pid[tools.i] = fork();
		if (tools.pid[tools.i] == 0)
		{
			ft_pipe_manager(tools, toc);
			child_export(export_var, envp, i, envp_size);
			ft_tocfree(&toc);
			ft_envp_free(envp);
			free_main(&tools);
			free_all(tools);
			exit(0);
		}
	}
	else
		add_to_env(&tools, &envp, &size, toc);
	if (tools.status_flag == 0 && size > 1)
	{
		tools.pid[tools.i] = fork();
		if (tools.pid[tools.i] == 0)
		{
			ft_pipe_manager(tools, toc);
			ft_tocfree(&toc);
			ft_envp_free(envp);
			free_main(&tools);
			free_all(tools);
			exit(0);
		}
	}
	g_exit_status = 0;
	return (envp);
}

void	child_export(char **export_var, char **envp, int i, int envp_size)
{
	int	j;

	j = 0;
	while (i < envp_size)
	{
		while (j > 0 && ft_strsort(envp[j - 1], envp[j]) < 0)
		{
			ft_swap(&envp[j - 1], &envp[j]);
			j--;
		}
		i++;
		j = i;
	}
	i = -1;
	while (envp[++i])
		print_env(export_var, envp, i);
}

void	print_env(char **export_var, char **envp, int i)
{
	int	j;

	j = 0;
	if (has_car(envp[i], '=') != -1)
	{
		export_var = separate_two(envp[i]);
		if (env_size(export_var) == 2)
			printf("export %s=\"%s\"\n", export_var[0], export_var[1]);
		else if (env_size(export_var) == 1
			&& envp[i][ft_strlen(envp[i]) - 1] == '=')
			printf("export %s=\"\"\n", export_var[0]);
		while (export_var[j])
			free(export_var[(j)++]);
		free(export_var);
	}
	else
		printf("export %s\n", envp[i]);
}

void	add_to_env(t_tools *tools, char ***envp, int *size, t_cmd toc)
{
	int	i;
	int		envp_size;


	i = 0;
	envp_size = env_size(*envp);
	while (i < *size - 1)
	{
		if (has_invalid_character(tools->args[i + 1]))
		{
			tools->status_flag = 1;
			tools->pid[tools->i] = fork();
			if (tools->pid[tools->i] == 0)
			{
				error_pipex_printf("export: %s: not a valid identifier\n",
					tools->args[i + 1]);
				ft_pipe_manager(*tools, toc);
				ft_tocfree(&toc);
				ft_envp_free(*envp);
				free_main(tools);
				free_all(*tools);
				exit(1);
			}
		}
		else
		{
			*envp = ft_addstr(*envp, tools->args[i + 1], envp_size);
			envp_size = env_size(*envp);
		}
		i++;
	}
}

// REMARQUE : Un nombre INCALCULABLE de cas specifiques en plus 
// 
// A gérer :
// [ok] export								
// -> affiche env par ordre alphabetique
// [ok] export MA_VAR						-> exporte juste MA_VAR
// [ok] export MA_VAR=x					-> exporte MA_VAR="x" dans export
// [ok] export MA_VAR='x'					-> idem
// [ok] export MA_VAR="x"					-> idem
// [ok] export M"A"VA'R'="x"				-> idem
// [ok] export MA_VAR=""					-> MA_VAR=""
// [ok] export MA_VAR						-> export et affiche juste MA_VAR
// [ok] export MA_VAR_QUI_EXISTE_DEJA=y	-> modifie la variable qui existe deja
// [**] export MA_VAR1=$MA_VAR2			-> MA_VAR1 prend la valeur de MA_VAR2
// [**] export MA_VAR1="$MA_VAR2"			-> idem
// [**] export MA_VAR1='$MA_VAR2'			
// -> MA_VAR1 pre  nd pour valeur : "MA_VAR2"
// [ok] export MA_VAR1=1 MA_VAR2=2			-> export les deux variables
// [ok] export MA_VAR1=MA_VAR2=2			
// -> MA_VAR1 prend la valeur "MA_VAR2=2"
// [ok] export MA@_VAR						-> Erreur syntaxe
// [ok] export 3MA_VAR						-> idem
// [ok] export =MA_VAR						-> idem
// [ok] export VAR+=TEXT
// [**] export VAR?=TEXT

// nota : utiliser ft_split !!!
