#include "../../incs/minishell.h"

int	arg_size(t_tools tools)
{
	int i;

	i = 0;
	while(tools.args[i])
		i++;
	return (i);
}

void	ft_swap(char **s1, char **s2)
{
	char *temp;
	temp = ft_strdup(*s1);
	*s1 = ft_strdup(*s2);
	*s2 = ft_strdup(temp);
}

int	env_size(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

int	ft_export(t_tools tools, char **envp)
{
	int i;
	int j;
	int size;
	int	envp_size;
	// char	**export_var;

	i = 0;
	j = 0;
	size = arg_size(tools);
	envp_size = env_size(envp);
	printf("ENVP SIZE : %d SIZE : %d\n\n\n", envp_size, size);
	if (size == 1)
	{
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
	}
	i = 0;
	while (envp[i])
	{
		pipex_printf("%s\n", envp[i]);
		i++;
	}
	// else
	// {
	// 	export_var = pipex_split(tools.args[1], " ");
	// 	while (export_var[i])
	// 	{
	// 		put_variable()
	// 	}
	// }
	return (0);
}

/*
A gérer :
[**] export MA_VAR=x					-> exporte MA_VAR=x dans env
[**] export MA_VAR='x'					-> idem
[**] export MA_VAR="x"					-> idem
[**] export MA_VAR=""					-> idem avec MA_VAR=
[**] export MA_VAR						-> n'exporte pas la variable !
[**] export MA_VAR_QUI_EXISTE_DEJA=y	-> modifie la variable qui existe deja
[**] export MA_VAR1=$MA_VAR2			-> MA_VAR1 prend la valeur de MA_VAR2
[**] export MA_VAR1="$MA_VAR2"			-> idem
[**] export MA_VAR1='$MA_VAR2'			-> MA_VAR1 prend pour valeur : "MA_VAR2"
[**] export MA_VAR1=1 MA_VAR2=2			-> export les deux variables
[**] export MA_VAR1=MA_VAR2=2			-> MA_VAR1 prend la valeur "MA_VAR2=2"
[**] export VAR+=TEXT
[**] export VAR?=TEXT

nota : utiliser ft_split !!!
*/