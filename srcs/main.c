#include "minishell.h"

int g_exit_status = 0;

static char *ft_prompt(void);
static void ft_loop(char ***envp, char *prompt);
static void ft_handler(int sig);

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	struct sigaction sa;
	struct sigaction sa_ignore;
	char *prompt;
	char **env_copy;

	sa_ignore.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_ignore, NULL);
	sa.sa_handler = ft_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);	
	prompt = ft_prompt();
	env_copy = ft_envp_dup(envp);
	ft_loop(&env_copy, prompt);
	return (free(prompt), ft_envp_free(env_copy), g_exit_status);
}

static void ft_loop(char ***envp, char *prompt)
{
	char *line_read;
	t_table_of_commands toc;

	while (1)
	{
		line_read = readline(prompt);
		if (!line_read)
		{
			printf("exit\n");
			rl_clear_history();
			return ;
		}
		else if (*line_read)
		{
			add_history(line_read);
			toc = ft_parser(line_read);
			if (toc.commands[0])
				pipex(toc, envp);
			ft_tocfree(&toc);
		}
		free(line_read);
	}
	rl_clear_history();
}

static void ft_handler(int sig)
{
	char *prompt;

	prompt = ft_prompt();
	if (sig == SIGINT)
	{
		rl_replace_line(prompt, 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 130;
	}
	else if (sig == SIGQUIT)
		write(1, "", 0);
	free(prompt);
}

static char *ft_prompt(void)
{
	char *prompt;
	const char *user;

	user = getenv("USER");
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
$>%n@%m %1~ %#		->Signifie que le prompt est au format suivant:	user@hostname cwd %
Nb : impossible d'affichier l'hostname sans la fonction uname(), gethostname() ou set()

Attention à check si toutes les variables existent pour ft_prompt

(Et, en principe, $PS2 est utilisé pour les prompt des heredocs)
*/
