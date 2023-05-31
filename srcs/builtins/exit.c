#include "minishell.h"

int	ft_exit(char *s, int exit_status)
{
	unsigned char	n;
	int 			sign;

	n = 0;
	sign = 1;
	while (*s == ' ')
		s++;
	if (!*s)
		return (exit_status);
	if (*s == '+' || *s == '-')
		sign = 44 - *(s++);
	if (!ft_isdigit(*s))
		return(ft_putendl_fd("exit: numeric argument required", 1), 255);
	while (ft_isdigit(*s))
		n = n * 10 + *(s++) - '0';
	while (*s == ' ')
		s++;
	if (*s)
		return(ft_putendl_fd("exit: too many arguments", 1), 255);
	return (sign * n);	
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