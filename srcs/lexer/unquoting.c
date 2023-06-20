#include "minishell.h"

static int	ft_remove_quotes(char **s, int idx, char c);

void	ft_unquote(char **s)
{
	int		idx;

	idx = -1;
	while ((*s)[++idx])
		if ((*s)[idx] == '\'' || (*s)[idx] == '\"')
			idx += ft_remove_quotes(s, idx, (*s)[idx]);
}

static int	ft_remove_quotes(char **s, int idx, char c)
{
	int		len;
	char	*new_s;

	len = 0;
	while ((*s)[idx + len + 1] && (*s)[idx + len + 1] != c)
		len++;
	new_s = malloc((ft_strlen(*s) - 1) * sizeof(*new_s));
	if (!new_s)
		exit(EXIT_FAILURE);
	ft_strlcpy(new_s, *s, idx + 1);
	ft_strlcpy(new_s + idx, *s + idx + 1, len + 1);
	ft_strlcpy(new_s + idx + len, *s + idx + len + 2, ft_strlen(*s) - idx - len - 1);
	free(*s);
	*s = new_s;
	return (len - 1);
}
