#include "minishell.h"

int	ft_envp_size(char **envp)
{
	int		size;

	size = 0;
	if (envp)
	{
		while (envp[size])
			size++;	
	}
	return (size);
}

char **ft_envp_realloc(char **old_envp, size_t new_size)
{
	char	**new_envp;
	int		old_size;

	old_size = ft_envp_size(old_envp);
	new_envp = malloc(new_size * sizeof(*new_envp));
	if (!new_envp)
		exit(EXIT_FAILURE);
	new_envp[old_size] = NULL;
	while (--old_size >= 0)
	{
		new_envp[old_size] = ft_strdup(old_envp[old_size]);
		free(old_envp[old_size]);
	}
	free(old_envp);
	return (new_envp);
}

void	ft_envp_free(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		free(envp[i]);
	free(envp);
}

char **ft_envp_dup(char **envp)
{
	int		size;
	char	**envp_dup;

	size = ft_envp_size(envp);
	envp_dup = malloc(size * sizeof(*envp_dup));
	if (!envp_dup)
		exit(EXIT_FAILURE);
	envp_dup[--size] = NULL;
	while (--size >= 0)
		envp_dup[size] = ft_strdup(envp[size]);
	return (envp_dup);	
}