/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:02:15 by jleguay           #+#    #+#             */
/*   Updated: 2023/07/06 21:56:10 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

static char	*ft_prompt(char **envp);
static void	ft_loop(char ***envp);
static void	ft_handler(int sig);

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sig_quit;
	struct sigaction	sig_int;
	char				**env_copy;

	(void) argv;
	(void) argc;
	if (isatty(0) != 1)
		return (1);
	ft_memset(&sig_int, 0, sizeof(sig_int));
	ft_memset(&sig_quit, 0, sizeof(sig_quit));
	sig_quit.sa_handler = SIG_IGN;
	sig_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sig_quit, NULL);
	sig_int.sa_handler = ft_handler;
	sig_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sig_int, NULL);
	env_copy = ft_envp_dup(envp);
	ft_loop(&env_copy);
	return (ft_envp_free(env_copy), g_exit_status);
}

static void	ft_loop(char ***envp)
{
	char		*prompt;
	char		*line_read;
	t_cmd_tab	toc;
	int			ret;

	ret = 0;
	while (!ret)
	{
		prompt = ft_prompt(*envp);
		line_read = readline(prompt);
		free(prompt);
		if (!line_read)
			ret = 1;
		else if (*line_read)
		{
			add_history(line_read);
			toc = ft_parser(line_read, *envp);
			ret = pipex(toc, envp);
			ft_tocfree(&toc);
			free(line_read);
		}
	}
	printf("exit\n");
	// rl_clear_history	();
}

static void	ft_handler(int sig)
{
	(void) sig;
	if (g_exit_status == -1)
		ioctl(STDIN_FILENO, TIOCSTI, "\0");
	else 
		write(1, "\n", 1);
	// rl_replace_line("", 0);
	// rl_on_new_line();
	// rl_redisplay();
	g_exit_status = 130;
}

static char	*ft_prompt(char **envp)
{
	char		*prompt;
	const char	*user;

	user = ft_getenv("USER", envp);
	if (!user)
		prompt = ft_strdup("%> ");
	else
		prompt = ft_strjoin(user, (" %> "));
	return (prompt);
}

/*
! théoriquement, le format du prompt est donné par la variable PS1:
Exemple:
$>echo $PS1
$>%n@%m %1~ %#		->Signifie que le prompt est au format suivant:
	user@hostname cwd %
Nb : impossible d'affichier l'hostname sans la fonction uname(),
	gethostname() ou set()

Attention à check si toutes les variables existent pour ft_prompt

(Et, en principe, $PS2 est utilisé pour les prompt des heredocs)
*/
