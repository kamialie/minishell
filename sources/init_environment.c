/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 16:11:50 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/21 15:19:11 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_environment(char **environ)
{
	size_t	i;
	char	**my_env;

	i = 0;
	while (environ[i] != NULL)
		++i;
	my_env = (char **)malloc(sizeof(*my_env) * (i + 1));
	i = 0;
	while (*environ != NULL)
	{
		if (ft_strstr(*environ, "SHELL"))
			my_env[i] = ft_strdup("SHELL=NEED TO ADD MY BINARY PLUS PATH");
		else if (ft_strstr(*environ, "SHLVL"))
			my_env[i] = ft_strjoin("SHLVL=", ft_itoa(ft_atoi(*environ + 6) + 1));
		else
			my_env[i] = ft_strdup(*environ);
		++i;
		++environ;
	}
	my_env[i] = NULL;
	return (my_env);
}
