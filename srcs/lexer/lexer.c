/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:01:21 by jleguay           #+#    #+#             */
/*   Updated: 2023/07/08 10:08:30 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_ismetachar(char c);
static int	ft_addoperator(char *s, t_list **tokens);
static int	ft_addword(char *s, t_list **tokens);
static void	ft_dissociate_op(t_list **tokens);

/* creation d'une liste chainee dont chaque element est 
un 'token' qui peut etre soit un 'operator' soit un 'word'*/
t_list	*ft_lexer(char *s, char **envp)
{
	t_list	*tokens;
	t_list	*last_token;

	(void) envp;
	tokens = NULL;
	while (*s)
	{
		while (*s == ' ' || *s == '\t')
			s++;
		if (ft_ismetachar(*s))
			s += ft_addoperator(s, &tokens);
		else if (*s)
		{
			s += ft_addword(s, &tokens);
			last_token = ft_lstlast(tokens);
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
		|| c == ')' || c == '<' || c == '>'
		|| c == ';');
}

static int	ft_addoperator(char *s, t_list **tokens)
{
	int		len;
	t_list	*last_elem;

	len = 0;
	while (ft_ismetachar(s[len]))
		len++;
	ft_lstadd_back(tokens, ft_lstnew(ft_substr(s, 0, len), OPERATOR));
	last_elem = ft_lstlast(*tokens);
	if (!ft_strncmp(last_elem->content, "|>", 3)
		|| !ft_strncmp(last_elem->content, "|<", 3)
		|| !ft_strncmp(last_elem->content, "|>>", 4)
		|| !ft_strncmp(last_elem->content, "|<<", 4))
		ft_dissociate_op(tokens);
	return (len);
}

static void	ft_dissociate_op(t_list **tokens)
{
	t_list	*last_elem;

	last_elem = ft_lstlast(*tokens);
	ft_lstadd_back(tokens, ft_lstnew(ft_substr(last_elem->content, 1,
				ft_strlen(last_elem->content) - 1), OPERATOR));
	free(last_elem->content);
	last_elem->content = ft_strdup("|");
}

static int	ft_addword(char *s, t_list **tokens)
{
	int		len;
	t_bool	simple_quote;
	t_bool	double_quote;

	len = 0;
	simple_quote = FALSE;
	double_quote = FALSE;
	while (s[len] && (simple_quote || double_quote
			|| !(ft_ismetachar(s[len]) || s[len] == ' ' || s[len] == '\t')))
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
