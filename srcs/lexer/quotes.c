/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:01:27 by jleguay           #+#    #+#             */
/*   Updated: 2023/07/02 17:39:50 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_remove_quotes(char **s, int idx, char c);

int	ft_check_quotes(char *word)
{
	int		idx;
	t_bool	simple_quote;
	t_bool	double_quote;

	idx = -1;
	simple_quote = FALSE;
	double_quote = FALSE;
	while (word[++idx])
	{
		if (word[idx] == '\"' && simple_quote == FALSE)
			double_quote = (double_quote == FALSE);
		else if (word[idx] == '\'' && double_quote == FALSE)
			simple_quote = (simple_quote == FALSE);
	}
	if (double_quote == FALSE && simple_quote == FALSE)
		return (1);
	g_exit_status = 258;
	if (double_quote == TRUE)
		ft_putendl_fd("syntax error: expected \" not found", 1);
	else if (simple_quote == TRUE)
		ft_putendl_fd("syntax error: expected \' not found", 1);
	return (0);
}

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
	ft_strlcpy(new_s + idx + len, *s + idx + len + 2,
		ft_strlen(*s) - idx - len - 1);
	free(*s);
	*s = new_s;
	return (len - 1);
}
