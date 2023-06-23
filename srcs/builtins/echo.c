#include "minishell.h"

int	ft_echo(char *s)
{
	int		n_flag;
	// t_bool	metacaracters;

	// metacaracters = TRUE;

	n_flag = 0;
	s += 5;
	if (*s == '-' && *(s + 1) == 'n' && *(s + 2) == ' ')
	{
		n_flag = 1;
		s += 3;
	}
	while (*s && *s != '\n')
	{
		if(*s != '\'' && *s != '\"')
			write(1, s, 1);
		s++;
	}
	if (!n_flag)
		write(1, "\n", 1);
	return (0);
}

/*
ATTENTION : echo renvoie les variables de shell, et non seulement les varaibles d'environnement.
-> il ne suffit pas de vérifier dans envp. En principe, aller vérifier du côté de ```set``` qui liste les variables shell (VAR=1 qui enregistre en variable shell versus ```export VAR=1``` qui enregistre comme variable d'environnement)

A gérer :
[**] echo "text"
[**] echo 'text'
[**] echo text
[**] echo "text" 'text' text
[**] echo $MA_VARIABLE
[**] echo '$MA_VAR'
[**] echo "$MA_VAR"
[**] echo $(MA_VAR)
[**] echo $?
[**] echo $$
[**] echo $!				-> PID of last job running in background
[**] echo -n text
*/