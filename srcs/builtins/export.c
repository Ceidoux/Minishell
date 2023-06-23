#include "../../incs/minishell.h"

int	ft_export(char *s, char **envp)
{
	(void) s;
	(void) envp;
	int i;

	i = 0;
	if (s == NULL)
	{
		while (envp[i])
		{
			pipex_printf("%s", envp[i]);
			i++;
		}
	}
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