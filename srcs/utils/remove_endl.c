#include "minishell.h"

/* Modifie la string pour remplacer le \n par \0 */
/* La fonction ne crée pas de nouvelle string */

char	*ft_remove_endl(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	if (str[len - 1] == '\n')
		str[len - 1] = '\0';
	return (str);
}
