/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 15:23:27 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/04 13:32:05 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_binary(char *command, t_bin *bins)
{
	char	*fbp;
	char	**folder;

	while (bins != NULL)
	{
		folder = bins->bins;
		while (*folder != NULL)
		{
			if (ft_strequ(*folder++, command))
			{
				fbp = ft_strjoin_mid(bins->dir, command, '/');
				return (fbp);
			}
		}
		bins = bins->next;
	}
	return (NULL);
}

void	command(char **arguments, char **envi, t_bin *bins)
{
	char	*fbp;
	pid_t	childPID;

	printf("bins - %p\n", bins);
	fbp = find_binary(*arguments, bins);
	if (fbp == NULL)
	{
		ft_putstr(NF_COMMAND);
		ft_putendl(arguments[0]);
	}
	else
	{
		childPID = fork();
		if (childPID >= 0)
		{
			if (childPID == 0)
				execve(fbp, arguments, envi);
			else
				wait(NULL);
		}
		else
			ft_putendl("fork failed");
		free(fbp);
	}
}
