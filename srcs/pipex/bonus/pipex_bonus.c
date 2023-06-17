/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 11:09:53 by kali              #+#    #+#             */
/*   Updated: 2023/06/17 17:22:14 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

ATTENTION : Version en travaux !!!

*/
#include "pipex_bonus.h"

int	main(int argc, char *argv[], char **envp)
{
	t_list	**my_list;
	t_list	*next_element;

	*my_list = ft_lstnew("<", OPERATOR);
	next_element = ft_lstnew("text1.txt", WORD);
	ft_lstadd_back(my_list, next_element);
	next_element = ft_lstnew("grep S", WORD);
	ft_lstadd_back(my_list, next_element);
	next_element = ft_lstnew("|", OPERATOR);
	ft_lstadd_back(my_list, next_element);
	next_element = ft_lstnew("grep e", WORD);
	ft_lstadd_back(my_list, next_element);
	next_element = ft_lstnew(">", OPERATOR);
	ft_lstadd_back(my_list, next_element);
	while ((*my_list)->next != NULL)
	{
		printf("%s\n", (*my_list)->next->content);
		(*my_list) = (*my_list)->next;
	}
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
