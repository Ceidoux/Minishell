#include "minishell.h"


int	is_slash_n(char *str)
{
	int i;

	i = 0;
	if (str[i] != '-')
		return (0);
	i++;
	if ((!str[i]) || (str[i] && str[i] != 'n'))
		return (0);
	while (str[i] == 'n')
		i++;
	if (str[i] && str[i] != ' ')
		return (0);
	return (i);
} 

void	ft_echo(t_tools tools, char *s, t_cmd_tab toc, char **envp)
{
	t_bool	n_flag;
	int j;
	char *copy;

	j = 0;
	if (toc.inputs[tools.i] != -1)
		dup2(toc.inputs[tools.i], STDIN_FILENO);
	else if (tools.i > 0)
		dup2(tools.pipe_fd[tools.i - 1][0], STDIN_FILENO);
	if (toc.outputs[tools.i] != -1)
		dup2(toc.outputs[tools.i], STDOUT_FILENO);
	else if (tools.i < toc.size - 1)
		dup2(tools.pipe_fd[tools.i][1], STDOUT_FILENO);
	n_flag = 0;
	while (j < toc.size)
	{
		if (tools.pipe_fd[j][0] >= 0)
			close(tools.pipe_fd[j][0]);
		if (tools.pipe_fd[j][1] >= 0)
			close(tools.pipe_fd[j][1]);
		if (toc.inputs[j] >= 0)
			close(toc.inputs[j]);
		if (toc.outputs[j] >= 0)
			close(toc.outputs[j]);
		j++;
	}
	j = 0;
	if (!s[4])
		ft_putchar_fd('\n', 1);
	else
	{
		s += 5;
		j = is_slash_n(s);
		if (/*!ft_strncmp(s, "-n", 2) && (s[2] == ' ' || s[2] == '\0')*/ j != 0)
		{

			n_flag = 1;
			s += j;
			while (*s && *s == ' ')
				s++;
		}
		copy = ft_strdup(s);
		ft_expand(&copy, envp);
		ft_unquote(&copy);
		if (n_flag)
			pipex_printf("%s", copy);
		else
			pipex_printf("%s\n", copy);
	}
	g_exit_status = 0;
	exit(0);
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

[] echo      test
[] echo "     " test

*/