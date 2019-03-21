/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 12:46:56 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/20 14:48:43 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **arguments)
{
	while (*arguments != NULL)
	{
		ft_putstr(*arguments);
		write(1, " ", 1);
		arguments++;
	}
	write(1, "\n", 1);
}

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

void	env(char *str, char **environ)
{
	if (str != NULL)
	{
		ft_putstr("env: ");
		ft_putstr(str);
		ft_putendl(": No such file or directory");
	}
	else
	{
		while (*environ != NULL)
		{
			ft_putendl(*environ);
			++environ;
		}
	}
}
