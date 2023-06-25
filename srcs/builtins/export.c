#include "../../incs/minishell.h"

int	arg_size(t_tools tools)   /*  Me permet d'avoir le nombres d'arguments passe (toos.args)*/
{
	int i;

	i = 0;
	while(tools.args[i])
		i++;
	return (i);
}

void	ft_swap(char **s1, char **s2)     /* Un simple echange de valeurs de str*/
{
	char *temp;
	temp = ft_strdup(*s1);
	*s1 = ft_strdup(*s2);
	*s2 = ft_strdup(temp);
}

int	env_size(char **envp)         /* Nombre de lignes dans env*/
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

int	has_car(char *str, char c)      /*  permet de saboir si un caractere est dans une chaine (notamment pour =, ' ou encore ")*/
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		(i)++;
	}
	return (-1);
}

int	is_char(char str, char c)      /*  permet de savoir si un caractere est le mem element)*/
{
	if (str == c)
		return (1);
	return (0);
}

char	**split_two(char *str, int i)
{
	int j;
	char **res;

	res = malloc(sizeof(char *) * 3);
	res[2] = NULL;
	j = 0;
	res[0] = malloc(sizeof(char) * i + 1);
	while (j < i)
	{
		res[0][j] = str[j];
		j++;
	}
	res[0][j] = 0;
	j = 0;
	res[1] = malloc(sizeof(char) * (ft_strlen(str) - i));
	i++;
	while (str[i])
	{
		res[1][j] = str[i];
		i++;
		j++;
	}
	res[1][j] = 0;
	return (res);
}

char	**separate_two(char	*str)
{
	char **res;
	int i;

	i = 0;
	while (str[i])
	{
		if (is_char(str[i], '=') && (size_t)i != (ft_strlen(str) - 1))
		{
			res = split_two(str, i);
			return (res);
		}
		i++;
	}
	res = malloc(sizeof(char *) * 2);
	res[1] = NULL;
	res[0] = malloc(sizeof(char) * ft_strlen(str));
	i = 0;
	while ((size_t)i < ft_strlen(str) - 1)
	{
		res[0][i] = str[i];
		i++;
	}
	res[0][i] = 0;
	return (res);
}

char	*modify_var(char *str)  /*  Fonction assez complexe permettant de mettre "" autour de la valeur de la variable apres le 1er signe '=' , 
									ainsi que de retirer tout ' ou " present dans la variable ! C'est un peu un "affinage" de la variable quoi */
{
	char	**res;
	int		i;
	// int flag;

	// flag = 0;
	i = 0;
	if (has_car(str, '\'') != -1 || has_car(str, '\"') != -1)
	{
		res = pipex_split(str, "'\"");
		i++;
		while (res[i])
		{
			res[0] = ft_strjoin(res[0], res[i]);
			i++;
		}
		i = 1;
		while(res[i])
		{
			free(res[i]);
			i++;
		}
		str = ft_strdup(res[0]);
		free(res[0]);
		free(res);
		i = 0;
	}
	// if (has_car(str, '=') != -1)
	// {
		// res = pipex_split(str, "=");
	// 	// res[0] = ft_strjoin(res[0], "=\"");
	// 	// i++;
	// 	// while(res[i])
	// 	// {
	// 	// 	if (flag == 1)
	// 	// 		res[0] = ft_strjoin(res[0], "=");
	// 	// 	else
	// 	// 		flag = 1;
	// 	// 	res[0] = ft_strjoin(res[0], res[i]);
	// 	// 	i++;
	// 	// }
	// 	// res[0] = ft_strjoin(res[0], "\"");
	// 	res = separate_two(str);
	// 	res[0] = ft_strjoin(res[0], "=\"");
	// 	i = 1;
	// 	while (res[i])
	// 	{
	// 		res[0] = ft_strjoin(res[0], res[i]);
	// 		i++;
	// 	}
	// 	res[0] = ft_strjoin(res[0], "\"");
	// 	i = 1;
	// 	while(res[i])
	// 	{
	// 		free(res[i]);
	// 		i++;
	// 	}
	// 	str = ft_strdup(res[0]);
	// 	free(res[0]);
	// 	free(res);
	// }
	return (str);
}

int	ft_len_dif(char *str)        /* permet de savoir combien de caracters avant le premier signe '=' (utile pour savoir s la variable existe deja avec strncmp() )*/
{
	int i;

	i = 0;
	if (has_car(str, '=') != -1)
	{
		while (str[i] != '=')
			i++;
		return (i);
	}
	else 
		return (ft_strlen(str));
}


int	has_invalid_character(char *str) /* verifie que la variable exportee respecte bien les regles de syntaxe */
{
	int i;

	i = 0;
	if ((str[i] >= '0' && str[i] <= '9') || str[i] == '=')
		return (1);
	while (str[i] && str[i] != '=')
	{
		if  ((str[i] < 'A'
				|| str[i] > 'Z') && (str[i] < 'a'
				|| str[i] > 'z') && (str[i] < '0' || str[i] > '9') 
				&& str[i] != '_' && str[i] != '=')
			return (1);
		i++;
	}
	return (0);
}

char	**ft_addstr(char **envp, char *str, int envp_size)  /*  apres avoir lisse la chaine avec modify_var(), permet de ajouter
															la variable dans envp ! */
{
	int		i;
	char	**res;

	i = 0;
	str = modify_var(str);
	while (envp[i])
	{
		if (pipex_strncmp(str, envp[i], ft_len_dif(str)) && has_car(str, '=') == -1
			&& ft_len_dif(str) == ft_len_dif(envp[i]))
			return (envp);
		if (pipex_strncmp(str, envp[i], ft_len_dif(str)) && ft_len_dif(str) == ft_len_dif(envp[i]))
		{
			free(envp[i]);
			envp[i] = ft_strdup(str);
			return (envp);
		}
		// if (pipex_strncmp(str, envp[i], ft_len_dif(str) - 1) && ft_len_dif(str) == ft_len_dif(envp[i]))
		i++;
	}
	i = 0;
	res = malloc(sizeof(char *) * (envp_size + 2));
	res[envp_size + 1] = NULL;
	while(envp_size > 0)
	{
		res[envp_size - 1] = ft_strdup(envp[envp_size - 1]);
		free(envp[envp_size - 1]);
		i++;
		envp_size--;
	}
	res[i] = ft_strdup(str);
	free(envp);
	return (res);
}

char	**ft_export(t_tools tools, char **envp)   /* fonction principale. Affiche env par ordre alphabetique si aucun paramtere, sinon
													export les variables selon des regles precises.*/
{
	int i;
	int j;
	int size;
	int	envp_size;
	char **export_var;

	i = 0;
	j = 0;
	size = arg_size(tools);
	envp_size = env_size(envp);
	if (size == 1)
	{
		while (i < envp_size)
		{
			while (j > 0 && ft_strsort(envp[j - 1], envp[j]) < 0)
			{
				ft_swap(&envp[j - 1], &envp[j]);
				j--;					
			}
			i++;
			j = i;
		}
		i = 0;
		j = 0;
		while (envp[i])
		{
			if (has_car(envp[i], '=') != -1)
			{
				export_var = separate_two(envp[i]);
				if (env_size(export_var) == 2)
					printf("export %s=\"%s\"\n", export_var[0], export_var[1]);
				else if (env_size(export_var) == 1 && envp[i][ft_strlen(envp[i]) - 1] == '=')
					printf("export %s=\"\"\n", export_var[0]);
				while (export_var[j])
					free(export_var[j++]);
				free(export_var);
			}
			else
				pipex_printf("export %s\n", envp[i]);
			i++;
		}
	}
	else
	{
		while (i < size - 1)
		{
			if (has_invalid_character(tools.args[i + 1]))
				printf("export: %s: not a valid identifier\n", tools.args[i + 1]);
			else
			{
				envp = ft_addstr(envp, tools.args[i + 1], envp_size);
				envp_size = env_size(envp);
			}
			i++;
		}
	}
	return (envp);
}

/*
A gérer :
[ok] export								-> affiche env par ordre alphabetique
[ok] export MA_VAR						-> exporte juste MA_VAR
[ok] export MA_VAR=x					-> exporte MA_VAR="x" dans export
[ok] export MA_VAR='x'					-> idem
[ok] export MA_VAR="x"					-> idem
[ok] export M"A"VA'R'="x"				-> idem
[ok] export MA_VAR=""					-> MA_VAR=""
[ok] export MA_VAR						-> export et affiche juste MA_VAR
[ok] export MA_VAR_QUI_EXISTE_DEJA=y	-> modifie la variable qui existe deja
[**] export MA_VAR1=$MA_VAR2			-> MA_VAR1 prend la valeur de MA_VAR2
[**] export MA_VAR1="$MA_VAR2"			-> idem
[**] export MA_VAR1='$MA_VAR2'			-> MA_VAR1 prend pour valeur : "MA_VAR2"
[ok] export MA_VAR1=1 MA_VAR2=2			-> export les deux variables
[ok] export MA_VAR1=MA_VAR2=2			-> MA_VAR1 prend la valeur "MA_VAR2=2"
[ok] export MA@_VAR						-> Erreur syntaxe
[ok] export 3MA_VAR						-> idem
[ok] export =MA_VAR						-> idem
[**] export VAR+=TEXT
[**] export VAR?=TEXT

nota : utiliser ft_split !!!
*/