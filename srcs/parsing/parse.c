#include "minishell.h"

static void	ft_cpy_var(char *var, char *dest, char **envp);
static int	ft_new_string_length(char *s, char **envp);
static int	ft_varname_len(char *s);


/* La fonction ft_parse supprime les simple quotes et double quotes
et expand les variables compris entre double quotes mais pas entre
simple quotes */
char	*ft_parse(char *s, char **envp)
{
	int		i;
	char	*new_s;
	t_bool	simple_quotes;
	t_bool	double_quotes;

	simple_quotes = FALSE;
	double_quotes = FALSE;
	new_s = malloc(ft_new_string_length(s) * sizeof(*new_s));
	if (!new_s)
		exit(EXIT_FAILURE);
	i = -1;
	while (s[++i])
	{
		if (s[i] == '\"')
			double_quotes = (double_quotes == FALSE);
		else if (s[i] == '\'')
			simple_quotes = (simple_quotes == FALSE);
		else if (s[i] == '$')
			ft_expand(*(s + i));

	}
}

static int	ft_new_string_length(char *s, char **envp)
{
	int	i;
	int length;
	t_bool	simple_quotes;

	simple_quotes = FALSE;
	i = -1;
	length = 0;
	while (s[++i])
	{
		if (s[i] == '\'')
			simple_quotes = (simple_quotes == FALSE);
		else if (s[i] == '$' && simple_quotes == FALSE)
		{
			length += ft_strlen(ft_get_var(s[i], envp, ft_varname_len(s[i])));
			while (s[i] && s[i] != ' ')
				i++;
		}
		else
			length++;
	}
	return (length);
}

static void	ft_cpy_var(char *var, char *dest, char **envp)
{

}

static int	ft_varname_len(char *s)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != ' ')
		len++;
	return (len);
}
