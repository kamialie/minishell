/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 16:11:50 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/26 19:37:04 by rgyles           ###   ########.fr       */
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

char	*get_envi_field(char *field, char **envi)
{
	while (*envi != NULL)
	{
		if (ft_strstr(*envi, field))
			return (*envi);
		++envi;
	}
	return (NULL);
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
	my_env = (char **)malloc(sizeof(*my_env) * (++size + flag)); //initialize last cell to NULL
	return (my_env);
}

char	**init_environment(char **environ)
{
	char	*lvl;
	char	**new_envi;
	char	**my_envi;

	new_envi = get_envi_array(environ, 0);
	my_envi = new_envi;
	while (*environ != NULL)
	{
		if (ft_strstr(*environ, "SHELL"))
			*new_envi = getcwd(NULL, 0); //need full path to binary
		else if (ft_strstr(*environ, "SHLVL"))
		{
			lvl = ft_itoa(ft_atoi(*environ + 6) + 1);
			*new_envi = ft_strjoin("SHLVL=", lvl);
			free(lvl);
		}
		else
			*new_envi = ft_strdup(*environ);
		++new_envi;
		++environ;
	}
	*new_envi = NULL;
	return (my_envi);
}
