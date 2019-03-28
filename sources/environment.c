/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 12:38:47 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/28 18:25:23 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_envi_field(char *line, char *field)
{
	int	i;

	i = 0;
	while (line[i] == field[i])
		i++;
	if (field[i] == '\0' && line[i] == '=')
		return (1);
	return (0);
}

char	*get_envi_field(char *field, char **envi)
{
	while (*envi != NULL)
	{
		if (find_envi_field(*envi, field))
			return (*envi);
		++envi;
	}
	return (NULL);
}

void	update_envi_field(char *field, char *new_line, char ***envi)
{
	char	**new_envi;

	new_envi = *envi;
	while (*new_envi != NULL)
	{
		if (find_envi_field(*new_envi, field))
		{
			free(*new_envi);
			*new_envi = new_line;
			return ;
		}
		++new_envi;
	}
}

char	**get_envi_array(char **envi, int flag)
{
	int		size;
	char	**my_env;

	size = 0;
	while (*envi++ != NULL)
		++size;
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
