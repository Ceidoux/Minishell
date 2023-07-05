/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:16:14 by smestre           #+#    #+#             */
/*   Updated: 2023/07/05 14:16:19 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	ft_cd_relative_path(char *path);
// static int	ft_cd_from_home(char *path);

// int		ft_cd(char *s)
// {
// 	int		ret;

// 	if (!*s || *(s + 1) == '~')
// 		ret = ft_cd_from_home(s);
// 	else if (*s != ' ')
// 		return (-1);
// 	else if (*(s + 1) == '-' && !*(s + 2))
// 		ret = chdir(getenv("OLDPWD"));
// 	else if (*(s + 1) == '/')
// 		ret = chdir(s + 1);
// 	else
// 		ret = ft_cd_relative_path(s + 1);
// 	if (ret)
// 		perror("cd");
// 	return (ret != 0);
// }

// static int	ft_cd_relative_path(char *path)
// {
// 	int		ret;
// 	char	*current_dir;
// 	char	*target_dir;

// 	current_dir = NULL;
// 	current_dir = getcwd(current_dir, 4096);
// 	if (!current_dir)
// 		return (1);
// 	target_dir = ft_strjoin(current_dir, "/");
// 	free(current_dir);
// 	current_dir = target_dir;
// 	target_dir = ft_strjoin(current_dir, path);
// 	free(current_dir);
// 	ret = chdir(target_dir);
// 	free(target_dir);
// 	return (ret);
// }

// static int	ft_cd_from_home(char *path)
// {
// 	int		ret;
// 	char	*home_dir;
// 	char	*target_dir;

// 	home_dir = getenv("HOME");
// 	if (!home_dir || !home_dir[0])
// 		return (0);
// 	if (!path || !path[0] || (path[1] == '~' && !path[2])
// 		|| (path[1] == '~' && path[2] == '/' && !path[3]))
// 		ret = chdir(home_dir);
// 	else
// 	{
// 		target_dir = ft_strjoin(home_dir, path + 2);
// 		ret = chdir(target_dir);
// 		free(target_dir);
// 	}
// 	return (ret);
// }




int	ft_cd(t_tools tools, char **envp)
{
	char	*str;

	if (arg_size(tools) > 2)
	{
		error_pipex_printf("%s: too many arguments\n");
		g_exit_status = 1;
		return (0);
	}
	if (arg_size(tools) == 1 || (arg_size(tools) == 2
		&& ft_strcmp(tools.args[1], "~")))
	{
		str = ft_getenv("HOME", envp);
		if (str == NULL)
		{
			perror(tools.args[0]);
			return (0);
		}
		if (chdir(str) == -1)
		{
			perror(str);
			g_exit_status = 1;
		}
	}
	else if (arg_size(tools) == 2)
	{
		if (chdir(tools.args[1]) == -1)
		{
			perror(tools.args[1]);
			g_exit_status = 1;
		}
	}
	return (0);
}
















/* 
____ A gérer ____

Output: 0 si succès, >0 si erreur (en pratique 1)

__ Absolute path:
[ok] cd /dir1/dir2/dir3
[ok] cd /dir1/dir2/dir3/

__ Relative path
[ok] cd dir1/dir2/dir3
[ok] cd dir1/dir2/dir3/
[ok] cd ..
[ok] cd ../relative_path
[ok] cd .
[ok] cd ./relative_path

_____ Doit peut-être être géré? ____
__ Variables
[**] cd $MA_VAR				e.g. cd $HOME ou cd $OLDDIR
[**] cd "$MA_VAR"
[**] cd '$MA_VAR'
[**] cd /usr/$MA_VAR
[**] cd	dir1/$MA_VAR

_____ N'a pas à être géré ____
__ History
[ok] cd -					-> retour vers le précédent répertoire

__ Home directory
[ok] cd						-> retour vers le home directory s'il exite (sinon rien)
[ok] cd ~					-> retour vers le home directory s'il exite (sinon rien)
[ok] cd ~/					-> retour vers le home directory s'il exite (sinon rien)
[ok] cd ~/directory			-> quid si home directory n'exite pas ?
Note : à vérifier, mais la ~ serait un expand que bash fait tout seul

__ Errors
[~] cd dir1 dir2			-> cd: string not in pwd

__ CDPATH
[**] export CDPATH=usr:usr/jle; cd documents

__ Symbolic links
(regarder cette notion)

Note : la variable CDPATH (vide à l'ouverture du shell) permet de 'stocker' le path de répertoire couramment utilisé.
Lors de l'utilisation de cd, la commande va vérifier l'existence d'un répertoire dans les pathname renseignés dans CDPATH
Exemple :
CDPATH=/usr/jle
cd documents -> regarde d'abord dans le répertoire courant (getcwd). Si documents n'existe pas, regarde ensuite si /urs/jle/documents existe
IDEM avec CDPATH=~/documents
Note : 
CDPATH peut contenir plusieurs pathname, séparé par des : e.g. usr:usr/jle:usr/jle/documents
Dans ce cas, les pathname sont testés successivement (en commençant toujours pas le current directory)


Véfirier le retour d'erreur, notamment pour cd- cd~ cd dir1 dir2 

En principe, cd doit gérer lui-même les . et les .. -> les . sont supprimés, les .. suppriment le dossier précédent s'il exite, s'il ne s'agit pas de root, et s'il ne s'agit pas d'un ..
De même, cd gère en principe lui-même le trailing / en le supprimant, et les // en les fusionnant (e.g. cd jle//Documents -> jle/Documents)

*/