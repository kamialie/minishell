/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 12:38:47 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/09 15:19:54 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**get_envi_array(char **envi, int flag)
{
	int		size;
	char	**my_env;

	size = 0;
	while (*envi++ != NULL)
		++size;
	my_env = (char **)malloc(sizeof(*my_env) * (size + flag + 1));
	my_env[size + flag] = NULL;
	return (my_env);
}

static char	*get_shell_path(char *str)
{
	char	*s1;
	char	*s2;
	char	*line;

	s1 = getcwd(NULL, 0);
	s2 = ft_strjoin(s1, "/");
	free(s1);
	s1 = ft_strjoin(s2, str);
	line = join_envi_line("SHELL", s1);
	free(s1);
	return (line);
}

char		**init_environment(char *str, char **environ)
{
	char	*lvl;
	char	**new_envi;
	char	**my_envi;

	new_envi = get_envi_array(environ, 1);
	my_envi = new_envi;
	while (*environ != NULL)
	{
		if (ft_strstr(*environ, "SHELL"))
			*new_envi = get_shell_path(str);
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
	*new_envi++ = ft_strdup("POLYANA=PrivetMoyDorogoyDrug");
	return (my_envi);
}
