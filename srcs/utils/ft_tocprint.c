/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tocprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleguay <jleguay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:06:02 by jleguay           #+#    #+#             */
/*   Updated: 2023/07/01 17:06:29 by jleguay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tocprint(t_cmd_tab	toc)
{
	int	line;

	line = 0;
	printf("Size = %d\n", toc.size);
	if (toc.size)
	{
		printf("[command][input fd][output fd]\n");
		while (line < toc.size)
		{
			printf("[%s]", toc.commands[line]);
			printf("[%d]", toc.inputs[line]);
			printf("[%d]", toc.outputs[line]);
			printf("\n");
			line++;
		}
	}
}
