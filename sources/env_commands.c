/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:59:28 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/26 12:03:51 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**set_envi(char **arguments, char **envi)
{
	int		i;
	char	*field;
	char	**my_env;

	i = 0;
	if (arguments[0] == NULL || arguments[1] == NULL || arguments[2] != NULL)
		return (NULL);
	field = ft_strjoin(*arguments, "=");
	my_env = get_envi_array(envi, 1);
	while (*envi != NULL)
	{
		my_env[i++] = ft_strdup(*envi);
		++envi;
	}
	free_envi_array(envi);
	*my_env = ft_strjoin(field, arguments[1]);
	free(field);
	my_env[i] = NULL;
	return (my_env);
}

char	**unset_envi(char **arguments, char **envi)
{
	int		i;
	char	*field;
	char	**my_env;

	i = 0;
	if (arguments[0] == NULL || arguments[1] != NULL)
		return (NULL);
	field = *arguments;
	my_env = get_envi_array(envi, -1);
	while (*envi != NULL)
	{
		if (ft_strstr(*envi, field) == NULL)
			my_env[i++] = ft_strdup(*envi);
		++envi;
	}
	free_envi_array(envi);
	*my_env = NULL;
	return (my_env);
}

void	print_envi(char *str, char **envi)
{
	if (str != NULL)
	{
		ft_putstr("env: ");
		ft_putstr(str);
		ft_putendl(": No such file or directory");
	}
	else
	{
		while (*envi != NULL)
		{
			ft_putendl(*envi);
			++envi;
		}
	}
}
