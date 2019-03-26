/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:59:28 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/26 17:30:30 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**set_envi(char **arguments, char **envi)
{
	char	*field;
	char	**new_envi;
	char	**my_envi;
	char	**old_envi;

	old_envi = envi;
	if (arguments[0] == NULL || arguments[1] == NULL || arguments[2] != NULL)
		return (NULL);
	field = ft_strjoin(*arguments, "=");
	new_envi = get_envi_array(envi, 1);
	my_envi = new_envi;
	while (*envi != NULL)
		*new_envi++ = ft_strdup(*envi++);
	free_envi_array(old_envi);
	*new_envi++ = ft_strjoin(field, arguments[1]);
	free(field);
	*new_envi = NULL;
	return (my_envi);
}

char	**unset_envi(char **arguments, char **envi)
{
	char	*field;
	char	**new_envi;
	char	**my_envi;
	char	**old_envi;

	old_envi = envi;
	if (arguments[0] == NULL || arguments[1] != NULL)
		return (NULL);
	field = *arguments;
	new_envi = get_envi_array(envi, -1);
	my_envi = new_envi;
	while (*envi != NULL)
	{
		if (ft_strstr(*envi, field) == NULL)
			*new_envi++ = ft_strdup(*envi++);
		else
			++envi;
	}
	free_envi_array(old_envi);
	*new_envi = NULL;
	return (my_envi);
}

void	print_envi(char *str, char **envi)
{
	if (str != NULL)
	{
		ft_putstr("env: ");
		ft_putstr(str);
		ft_putendl(NF_FOD);
		return ;
	}
	while (*envi != NULL)
		ft_putendl(*envi++);
}
