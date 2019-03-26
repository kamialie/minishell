/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:55:36 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/26 20:00:45 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_envi_line(char *field, char *value)
{
	char	*line;
	char	*new;

	new = (char *)malloc(sizeof(*line) * (ft_strlen(field) + ft_strlen(value) + 2));
	line = new;
	while (*field != '\0')
		*new++ = *field++;
	*new++ = '=';
	while (*value != '\0')
		*new++ = *value++;
	*new = '\0';
	return (line);
}

int	find_envi_field(char *line, char *field)
{
	while (*line != '=')
	{
		if (*line != *field)
			return (0);
		++line;
		++field;
	}
	return (1);
}

char	**update_envi(char **envi)
{
	int	i;
	char	*new_pwd;
	char	*old_pwd;
	char	**tmp;
	char	**new_envi;

	i = 0;
	tmp = envi;
	new_envi = get_envi_array(envi, 0);
	while (*envi != NULL)
	{
		if (find_envi_field(*envi, "PWD"))
		{
			old_pwd = ft_strdup(*envi + 4);
			++envi;
		}
		else if (find_envi_field(*envi, "OLDPWD"))
			++envi;
		else
			new_envi[i++] = ft_strdup(*envi++);
	}
	free_envi_array(tmp);
	new_pwd = getcwd(NULL, 0);
	new_envi[i++] = join_envi_line("PWD", new_pwd);
	free(new_pwd);
	new_envi[i++] = join_envi_line("OLDPWD", old_pwd);
	free(old_pwd);
	new_envi[i] = NULL;
	return (new_envi);
}

char	**change_direct(char **arguments, char **envi)
{
	int	check;
	char	*path;
	
	if (*arguments == NULL)
	{
		if ((path = get_envi_field("HOME", envi)) == NULL)
			ft_putendl(NF_HD);
		else if ((check = chdir(path + 5)) != 0)
			ft_putendl(ER_CD);
	}
	else if (ft_strequ(*arguments, "-"))
	{
		if ((path = get_envi_field("OLDPWD", envi)) == NULL)
			ft_putendl(NF_OLDPWD);
		else if ((check = chdir(path + 7)) != 0)
			ft_putendl(ER_CD);
	}
	return (update_envi(envi));
}
