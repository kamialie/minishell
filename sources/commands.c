/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 15:23:27 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/11 12:31:56 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_binary(char *fbp, char **arguments, char **envi)
{
	pid_t	childpid;

	childpid = fork();
	if (childpid >= 0)
	{
		if (childpid == 0)
			execve(fbp, arguments, envi);
		else
			wait(NULL);
	}
	else
		ft_putendl("fork failed");
}

static char	*find_binary(char *command, t_bin *bins)
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

void		command(char **arguments, char **envi, t_bin *bins)
{
	char	*fbp;

	fbp = find_binary(*arguments, bins);
	if (fbp == NULL)
	{
		ft_putstr(NF_COMMAND);
		ft_putendl(arguments[0]);
	}
	else
	{
		execute_binary(fbp, arguments, envi);
		free(fbp);
	}
}

void		command_path(char **arguments, char **envi)
{
	char	*fbp;

	fbp = *arguments;
	if (access(fbp, F_OK) == -1)
	{
		ft_putstr(NF_FOD_CD);
		ft_putendl(fbp);
	}
	else if (access(fbp, X_OK) == -1)
	{
		ft_putstr(ER_EX);
		ft_putendl(fbp);
	}
	else
		execute_binary(fbp, arguments, envi);
}
