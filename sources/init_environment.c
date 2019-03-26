/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 16:11:50 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/26 11:57:57 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envi_array(char **envi)
{
	int	i;

	i = 0;
	while (envi[i] != NULL)
	{
		free(envi[i]);
		++i;
	}
	free(envi);
}

char	**get_envi_array(char **envi, int flag)
{
	int		size;
	char	**my_env;

	size = 0;
	while (*envi != NULL)
	{
		++envi;
		++size;
	}
	my_env = (char **)malloc(sizeof(*my_env) * (++size + flag));
	return (my_env);
}

char	**init_environment(char **environ)
{
	int		i;
	char	*lvl;
	char	**my_env;

	i = 0;
	my_env = get_envi_array(environ, 0);
	while (*environ != NULL)
	{
		if (ft_strstr(*environ, "SHELL"))
			my_env[i] = getcwd(NULL, 0); //need full path to binary
		else if (ft_strstr(*environ, "SHLVL"))
		{
			lvl = ft_itoa(ft_atoi(*environ + 6) + 1);
			my_env[i] = ft_strjoin("SHLVL=", lvl);
			free(lvl);
		}
		else
			my_env[i] = ft_strdup(*environ);
		++environ;
		++i;
	}
	my_env[i] = NULL;
	return (my_env);
}
