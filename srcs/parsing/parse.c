#include "minishell.h"

static int	ft_ismetachar(char c);
static int	ft_addoperator(char *s, t_list **tokens);
static int ft_addword(char *s, t_list **tokens);

/* creation d'une liste chainee dont chaque element est 
un 'token' qui peut etre soit un 'operator' soit un 'word'*/
t_list *ft_parse(char *s)
{
	t_list	*tokens;

	tokens = NULL;
	while (*s)
	{
		if (ft_ismetachar(*s))
			s += ft_addoperator(s, &tokens);
		else
			s += ft_addword(s, &tokens);
	}
	return (tokens);
}

static int	ft_ismetachar(char c)
{
	return (c == '|' || c == '&' || c == '('
		|| c == ')' || c == '<' || c == '>');
}
static int	ft_addoperator(char *s, t_list **tokens)
{
	int	len;

	len = 0;
	while(ft_ismetachar(s[len]))
		len++;
	ft_lstadd_back(tokens, ft_lstnew(ft_substr(s, 0, len), OPERATOR));
	return (len);
}

static int ft_addword(char *s, t_list **tokens)
{
	int		len;
	int		start;
	t_bool	simple_quote;
	t_bool	double_quote;

	start = 0;
	len = 0;
	simple_quote = FALSE;
	double_quote = FALSE;
	while (s[start] == ' ')
		start++;
	while (s[start + len] && (simple_quote || double_quote || !ft_ismetachar(s[start + len])))
	{
		if (s[start + len] == '\"' && simple_quote == FALSE)
			double_quote = (double_quote == FALSE);
		else if (s[start + len] == '\'' && double_quote == FALSE)
			simple_quote = (simple_quote == FALSE);
		len++;
	}
	while (len && s[start + len - 1] == ' ')
		len--;
	ft_lstadd_back(tokens, ft_lstnew(ft_substr(s, start, len), WORD));
	while (s[start + len] == ' ')
		len++;
	return (start + len);
}

