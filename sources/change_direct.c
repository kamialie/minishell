/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_direct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 10:17:07 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/28 16:43:37 by rgyles           ###   ########.fr       */
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

/*char	**update_envi(char **envi)
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
			old_pwd = ft_strdup(*envi++ + 4);
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
}*/

void	go_to_path(char *path)
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
		}
		else
		{
			ft_putstr(ND_CD);
			ft_putendl(path);
		}
	}
}

void	change_direct(char **arguments, char ***envi)
{
	char	*path;
	
	if (*arguments != NULL && *(arguments + 1) != NULL)
	{
		ft_putendl(TMA_CD);
		return ;
	}
	if (*arguments == NULL || ft_strequ(*arguments, "~"))
	{
		if ((path = get_envi_field("HOME", *envi)) == NULL)
			ft_putendl(NF_HD_CD);
		else if (chdir(path + 5) != 0)
			ft_putendl(ER_CD);
	}
	else if (ft_strequ(*arguments, "-"))
	{
		if ((path = get_envi_field("OLDPWD", *envi)) == NULL)
			ft_putendl(NF_OLDPWD_CD);
		else if (chdir(path + 7) != 0)
			ft_putendl(ER_CD);
		else
			ft_putendl(path + 7);
	}
	else
		go_to_path(*arguments);
	update_envi_field("OLDPWD", ft_strdup(get_envi_field("PWD", *envi) + 4), envi);
	update_envi_field("PWD", getcwd(NULL, 0), envi);
}
