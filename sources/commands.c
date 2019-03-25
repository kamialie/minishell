/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 15:23:27 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/25 18:13:57 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(char *str, char **environ)
{
	if (str != NULL)
		ft_putendl(I_PWD);
	else
	{
		while (*environ != NULL)
		{
			if (ft_strstr(*environ, "PWD"))
			{
				ft_putendl(*environ + 4);
				return ;
			}
			++environ;
		}
	}
}

void	env(char *str, char **my_env)
{
	if (str != NULL)
	{
		ft_putstr("env: ");
		ft_putstr(str);
		ft_putendl(": No such file or directory");
	}
	else
	{
		while (*my_env != NULL)
		{
			ft_putendl(*my_env);
			++my_env;
		}
	}
}

void	command(char **commands, char **my_env)
{
	pid_t	childPID;

	childPID = fork();
	if (childPID >= 0)
	{
		if (childPID == 0)
			execve("/bin/pwd", commands, my_env);
		else
			wait(NULL);
	}
	else
		ft_putendl("fork failed");
}
