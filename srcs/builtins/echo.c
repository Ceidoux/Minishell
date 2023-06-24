#include "minishell.h"

int	ft_echo(char *s)
{
	t_bool	n_flag;

	n_flag = 0;

	s += 5;
	printf("%s %c\n", s, s[2]);
	if (!ft_strncmp(s, "-n", 2) && s[2] == ' ')
	{
		n_flag = 1;
		s += 3;
	}
	if (n_flag)
		ft_putstr_fd(s, 1);
	else
		ft_putendl_fd(s, 1);
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