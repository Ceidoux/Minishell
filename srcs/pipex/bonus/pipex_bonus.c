/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 11:09:53 by kali              #+#    #+#             */
/*   Updated: 2023/06/19 15:42:19 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

ATTENTION : Version en travaux !!!

Cette version inclut une liste initialisee dans le main en guise d'exemple.

LISTE EXEMPLE ACTUELLE : < text1.txt grep "S" | grep "e" > text2.txt

REMARQUE : Une partie du code actuel est encore ecrit en PSEUDO-CODE.

*/
#include "pipex_bonus.h"

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strjoin_space(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (res == NULL)
		return (res);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = ' ';
	i++;
	while (s2[j])
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = 0;
	free(s1);
	return (res);
}

void	manage_word(t_list **my_list, t_tools *tools, char **envp)
{
	char *full_command;

	full_command = ft_strdup((*my_list)->content);
	(*my_list) = (*my_list)->next;
	while ((*my_list) && (*my_list)->type == WORD)
	{
		full_command = ft_strjoin_space(full_command, (*my_list)->content);
		(*my_list) = (*my_list)->next;
	}
	tools->saved_std_out = dup(1);
	tools->args = ft_split(full_command, ' ');
	if (tools->i - 1 >= 0)
		dup2(tools->pipe_fd[tools->i - 1][0], STDIN_FILENO);
	if ((*my_list) && ft_strcmp((*my_list)->content, ">"))
	{
		(*my_list) = (*my_list)->next;
		tools->pipe_fd[tools->i][1] = open((*my_list)->content, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		(*my_list) = (*my_list)->next;
	}
	dup2(tools->pipe_fd[tools->i][1], STDOUT_FILENO);
	tools->j = 0;
	while (tools->j < tools->nombre_fds)
	{
		close(tools->pipe_fd[tools->j][0]);
		close(tools->pipe_fd[tools->j][1]);
		(tools->i)++;
	}
	tools->j = 0;
	close(tools->saved_std_out);
	if (is_slash(tools->args[0]))
		absolute_relative_path(*tools);
	else
		env_path(*tools, envp);
}

void	manage_operator(t_list **my_list, t_tools *tools, char **envp)
{
	if (ft_strcmp((*my_list)->content, "<"))
	{
		*my_list = (*my_list)->next;
		// if (tools->i - 1 >= 0)
		tools->pipe_fd[tools->i][1] = open((*my_list)->content, O_RDONLY, 0644);
		tools->j = 0;
		while (tools->j < tools->nombre_fds)
		{
			close(tools->pipe_fd[tools->j][0]);
			close(tools->pipe_fd[tools->j][1]);
			(tools->j)++;
		}
		*my_list = (*my_list)->next;
		exit(0);
	}
	else if (ft_strcmp((*my_list)->content, "|"))
	{
		(*my_list) = (*my_list)->next;
		if ((*my_list)->type == WORD)
			manage_word(my_list, tools, envp);
		else	
			manage_operator(my_list, tools, envp);
	}
	else if (ft_strcmp((*my_list)->content, ">"))
	{
		*my_list = (*my_list)->next;
		tools->pipe_fd[tools->i][1] = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		tools->j = 0;
		while (tools->j < tools->nombre_fds)
		{
			close(tools->pipe_fd[tools->j][0]);
			close(tools->pipe_fd[tools->j][1]);
			(tools->j)++;
			*my_list = (*my_list)->next;
			exit(0);
		}
		
	}
}


int	fd_count(t_list *my_list)
{
	int	compteur;

	compteur = 0;
	while (my_list)
	{
		if (my_list->type == OPERATOR)
		{
			if (ft_strcmp(my_list->content, "<") || ft_strcmp(my_list->content, ">"))
			{
				my_list = my_list->next;
				my_list = my_list->next;
			}
			else
			{
				my_list = my_list->next;
				while (my_list && my_list->type == WORD)
					my_list = my_list->next;
			}
			compteur++;
		}
		else
		{
			compteur++;
			while (my_list && my_list->type == 	WORD)
				my_list = my_list->next;
		}
	}
	return (compteur);
}

void	print_list(t_list **my_list)
{
	while ((*my_list) != NULL)
	{
		printf("%s : %d\n", (*my_list)->content, (*my_list)->type);
		(*my_list) = (*my_list)->next;
	}
}


int	main(int argc, char *argv[], char **envp)
{
	t_list	**my_list;
	t_list	*next_element;
	int		nombre_fds;
	t_tools tools;

	my_list = malloc(sizeof(t_list *));
	*my_list = ft_lstnew("<", OPERATOR);
	next_element = ft_lstnew("text1.txt", WORD);
	ft_lstadd_back(my_list, next_element);
	next_element = ft_lstnew("grep", WORD);
	ft_lstadd_back(my_list, next_element);
	next_element = ft_lstnew("S", WORD);
	ft_lstadd_back(my_list, next_element);
	next_element = ft_lstnew("|", OPERATOR);
	ft_lstadd_back(my_list, next_element);
	next_element = ft_lstnew("grep", WORD);
	ft_lstadd_back(my_list, next_element);
	next_element = ft_lstnew("e", WORD);
	ft_lstadd_back(my_list, next_element);
	next_element = ft_lstnew(">", OPERATOR);
	ft_lstadd_back(my_list, next_element);
	next_element = ft_lstnew("text2.txt", WORD);
	ft_lstadd_back(my_list, next_element);
	// print_list(my_list);
	nombre_fds = fd_count(*my_list);
	printf("NUMBER OF PIPES: %d", nombre_fds);
	init_tools(&tools, nombre_fds);
	tools.nombre_fds = nombre_fds;
	while ((*my_list))
	{
		tools.pid[tools.i] = fork();
		if (tools.pid[tools.i] == 0)
		{
			if (ft_strcmp((*my_list)->type, OPERATOR))
				manage_operator(my_list, &tools, char **envp);
			else
				manage_word(my_list, &tools, char **envp);
		}
		tools.i += 1;
	}
	// }
	// // while(*my_list)
	// {
	// 	if ((*my_list)->type == WORD)
	// 	{
	// 		manage_word();
	// 	}
	// 	else
	// 	{
	// 		manage_operator();
	// 	}
	// }
	return (0);
}

// int	pipex(int argc, char *argv[], char **envp)
// {
// 	t_tools	tools;

// 	if (argc < 5)
// 		return (syntax_help());
// 	init_tools(&tools, argc);
// 	first_part(tools, argc, argv, envp);
// 	tools.i = 3;
// 	while (tools.i < argc - 2)
// 	{
// 		tools.pid[tools.i - 2] = fork();
// 		if (tools.pid[tools.i - 2] == 0)
// 		{
// 			if (non_printable(argv[tools.i]))
// 			{
// 				syntax_help();
// 				free_main(&tools);
// 				exit(0);
// 			}
// 			middle_commands(tools, argc, argv[tools.i], envp);
// 		}
// 		(tools.i)++;
// 	}
// 	last_part(tools, argv, envp);
// 	clean_finish(tools, argc);
// 	return (0);
// }

// void	clean_finish(t_tools tools, int argc)
// {
// 	tools.i = 0;
// 	while (tools.i < argc - 2)
// 	{
// 		close(tools.pipe_fd[tools.i][0]);
// 		close(tools.pipe_fd[tools.i][1]);
// 		(tools.i)++;
// 	}
// 	while (argc > 2)
// 	{
// 		wait(NULL);
// 		argc--;
// 	}
// 	free_main(&tools);
// }

// void	first_command(t_tools tools, int argc, char *argv[], char **envp)
// {
// 	int	i;
// 	int	first_fd;

// 	i = 1;
// 	while (i < argc - 2)
// 	{
// 		close(tools.pipe_fd[i][0]);
// 		close(tools.pipe_fd[i][1]);
// 		i++;
// 	}
// 	tools.saved_std_out = dup(1);
// 	tools.i = 0;
// 	tools.args = ft_split(argv[2], ' ');
// 	first_fd = open(argv[1], O_RDONLY, 0644);
// 	if (first_fd == -1)
// 		failed_open(tools, argv);
// 	dup2(first_fd, STDIN_FILENO);
// 	dup2(tools.pipe_fd[0][1], STDOUT_FILENO);
// 	close_rest_1(tools, first_fd);
// 	tools.i = 0;
// 	if (is_slash(tools.args[0]))
// 		absolute_relative_path(tools);
// 	else
// 		env_path(tools, envp);
// }

// void	middle_commands(t_tools tools, int argc, char *argv, char **envp)
// {
// 	tools.saved_std_out = dup(1);
// 	tools.args = ft_split(argv, ' ');
// 	dup2(tools.pipe_fd[(tools.i - 1) - 2][0], STDIN_FILENO);
// 	dup2(tools.pipe_fd[(tools.i - 1) - 1][1], STDOUT_FILENO);
// 	tools.i = 0;
// 	while (tools.i < argc - 2)
// 	{
// 		close(tools.pipe_fd[tools.i][0]);
// 		close(tools.pipe_fd[tools.i][1]);
// 		(tools.i)++;
// 	}
// 	tools.i = 0;
// 	close(tools.saved_std_out);
// 	if (is_slash(tools.args[0]))
// 		absolute_relative_path(tools);
// 	else
// 		env_path(tools, envp);
// }

// void	last_command(t_tools tools, char *argv, char *file, char **envp)
// {
// 	int	i;
// 	int	final_fd;

// 	i = tools.i - 1;
// 	tools.saved_std_out = dup(1);
// 	final_fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
// 	tools.args = ft_split(argv, ' ');
// 	dup2(tools.pipe_fd[(tools.i - 1) - 2][0], STDIN_FILENO);
// 	dup2(final_fd, STDOUT_FILENO);
// 	tools.i = 0;
// 	while (tools.i < i + 1)
// 	{
// 		close(tools.pipe_fd[tools.i][0]);
// 		close(tools.pipe_fd[tools.i][1]);
// 		(tools.i)++;
// 	}
// 	close(tools.saved_std_out);
// 	close(final_fd);
// 	tools.i = 0;
// 	if (is_slash(tools.args[0]))
// 		absolute_relative_path(tools);
// 	else
// 		env_path(tools, envp);
// }
