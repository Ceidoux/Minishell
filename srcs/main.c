#include "minishell.h"

int g_exit_status = 0;

static char *ft_prompt(char **envp);
static void ft_loop(char ***envp);
static void ft_handler(int sig);

int main(int argc, char **argv, char **envp)
{
	struct sigaction	sig_quit;
	struct sigaction	sig_int;
	char				**env_copy;

	(void)argc;
	(void)argv;
	ft_bzero(&sig_int, sizeof(sig_int));
	sig_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig_quit, NULL);
	ft_bzero(&sig_quit, sizeof(sig_quit));
	sig_int.sa_handler = ft_handler;
	sigaction(SIGINT, &sig_int, NULL);	
	env_copy = ft_envp_dup(envp);
	ft_loop(&env_copy);
	return (ft_envp_free(env_copy), g_exit_status);
}

static void ft_loop(char ***envp)
{
	char				*prompt;
	char				*line_read;
	t_table_of_commands toc;

	while (1)
	{
		prompt = ft_prompt(*envp);
		line_read = readline(prompt);
		if (!line_read)
		{
			printf("exit\n");
			rl_clear_history();
			free(prompt);
			return ;
		}
		else if (*line_read)
		{
			add_history(line_read);
			toc = ft_parser(line_read, *envp);
			if (toc.commands[0])
				pipex(toc, envp);
			ft_tocfree(&toc);
		}
		free(line_read);
	}
	free(prompt);
	rl_clear_history();
}

static void ft_handler(int sig)
{
	(void) sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 130;
}

static char *ft_prompt(char **envp)
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
$>%n@%m %1~ %#		->Signifie que le prompt est au format suivant:	user@hostname cwd %
Nb : impossible d'affichier l'hostname sans la fonction uname(), gethostname() ou set()

Attention à check si toutes les variables existent pour ft_prompt

(Et, en principe, $PS2 est utilisé pour les prompt des heredocs)
*/
