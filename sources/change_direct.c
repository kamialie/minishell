/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_direct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 10:17:07 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/11 12:52:44 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	go_to_path(char *path)
{
	struct stat	file_stat;

	if (access(path, F_OK) == -1)
	{
		ft_putstr(NF_FOD_CD);
		ft_putendl(path);
	}
	else
	{
		stat(path, &file_stat);
		if (S_ISDIR(file_stat.st_mode))
		{
			if (chdir(path) != 0)
				ft_putendl(ER_CD);
			else
				return (1);
		}
		else
		{
			ft_putstr(ND_CD);
			ft_putendl(path);
		}
	}
	return (0);
}

static int	go_to_oldpwd(char **envi)
{
	char *path;

	if ((path = get_envi_field("OLDPWD", envi)) == NULL)
		ft_putendl(NF_OLDPWD_CD);
	else if (chdir(path + 7) != 0)
		ft_putendl(ER_CD);
	else
	{
		ft_putendl(path + 7);
		return (1);
	}
	return (0);
}

static void	update_envi(char ***envi)
{
	char	*value;

	value = ft_strdup(get_envi_field("PWD", *envi) + 4);
	update_envi_field("OLDPWD", value, envi);
	free(value);
	value = getcwd(NULL, 0);
	update_envi_field("PWD", value, envi);
	free(value);
}

void		change_direct(char **arguments, char ***envi)
{
	int		success;
	char	*path;

	success = 0;
	if (*arguments != NULL && *(arguments + 1) != NULL)
		ft_putendl(TMA_CD);
	else if (*arguments == NULL || ft_strequ(*arguments, "~"))
	{
		if ((path = get_envi_field("HOME", *envi)) == NULL)
			ft_putendl(NF_HD_CD);
		else if (chdir(path + 5) != 0)
			ft_putendl(ER_CD);
		else
			success = 1;
	}
	else if (ft_strequ(*arguments, "-"))
		success = go_to_oldpwd(*envi);
	else
		success = go_to_path(*arguments);
	if (success)
		update_envi(envi);
}
