#include "minishell.h"

void	ft_exit(char *s)
{
	unsigned char	n;
	int 			sign;

	n = 0;
	sign = 1;
	s += 4;
	while (*s == ' ')
		s++;
	if (!*s)
		return ;
	if (*s == '+' || *s == '-')
		sign = 44 - *(s++);
	if (!ft_isdigit(*s))
	{
		ft_putendl_fd("exit: numeric argument required", 2);
		g_exit_status = 2;
		return ;
	}
	while (ft_isdigit(*s))
		n = n * 10 + *(s++) - '0';
	while (*s == ' ')
		s++;
	if (*s)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		g_exit_status = 1;
		return ;
	}
	g_exit_status = sign * n;
}

/*
A gérer:
[ok] exit						-> If N is not given, the exit status code is that of the last executed command
[ok] exit [space][space][space] -> renvoie le dernier statut de sortie (identique à exit)
[ok] exit N						-> returns N (avec N unsigned char)
[ok] exit -N					-> renvoie la valeur en unsigned char
[ok] exit 123D					-> print error: numeric argument required ET exit avec 255 en return value
[ok] exit D123					-> idem
[~] exit 123 123				-> print error: too many arguments (MAIS en principe n'exit pas)
Note: exit ne gère pas l'overflow ! (exit 256 renvoie 0)
*/