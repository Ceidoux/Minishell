#include "minishell.h"

static int	ft_ismetachar(char c);
static int	ft_isblank(char c);
static int	ft_addoperator(char *s, t_list **tokens);
static int	ft_addword(char *s, t_list **tokens);

/* creation d'une liste chainee dont chaque element est 
un 'token' qui peut etre soit un 'operator' soit un 'word'*/
t_list *ft_parse(char *s, char **envp)
{
	t_list	*tokens;
	t_list	*last_token;

	tokens = NULL;
	while (*s)
	{
		while (ft_isblank(*s))
			s++;
		if (ft_ismetachar(*s))
			s += ft_addoperator(s, &tokens);
		else if (*s)
		{
			s += ft_addword(s, &tokens);
			last_token = ft_lstlast(tokens);
			ft_expand(&(last_token->content), envp);
			ft_unquote(&(last_token->content));
			if (last_token->content[0] == '\0')
				ft_lstremovelast(&tokens, &free);
		}
	}
	if (!ft_check(tokens))
		ft_lstclear(&tokens, &free);
	return (tokens);
}

static int	ft_ismetachar(char c)
{
	return (c == '|' || c == '&' || c == '('
		|| c == ')' || c == '<' || c == '>');
}

static int	ft_isblank(char c)
{
	return (c == ' ' || c == '\t');
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
	t_bool	simple_quote;
	t_bool	double_quote;

	len = 0;
	simple_quote = FALSE;
	double_quote = FALSE;
	while (s[len] && (simple_quote || double_quote || !(ft_ismetachar(s[len]) || ft_isblank(s[len]))))
	{
		if (s[len] == '\"' && simple_quote == FALSE)
			double_quote = (double_quote == FALSE);
		else if (s[len] == '\'' && double_quote == FALSE)
			simple_quote = (simple_quote == FALSE);
		len++;
	}
	ft_lstadd_back(tokens, ft_lstnew(ft_substr(s, 0, len), WORD));
	return (len);
}
