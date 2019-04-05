/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:59:28 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/05 12:58:27 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_envi(char **arguments, char ***envi, t_bin **bins)
{
	char	*field;
	char	**p;
	char	**new_envi;
	char	**tmp_envi;
	char	**old_envi;

	if (arguments[0] == NULL || arguments[1] == NULL || arguments[2] != NULL)
	{
		ft_putendl(WN_SETENV);
		return ;
	}
	field = ft_strjoin(*arguments, "=");
	new_envi = get_envi_array(*envi, 1);
	old_envi = *envi;
	p = old_envi;
	tmp_envi = new_envi;
	while (*p != NULL)
		*tmp_envi++ = ft_strdup(*p++);
	free_envi_array(old_envi);
	*tmp_envi++ = ft_strjoin(field, arguments[1]);
	*tmp_envi = NULL;
	if (ft_strequ(field, "PATH="))
		init_binaries(get_envi_field("PATH", new_envi) + 5, bins);
	free(field);
	*envi = new_envi;
}

void	unset_envi(char **arguments, char ***envi, t_bin **bins)
{
	char	**new_envi;
	char	**envi_head;
	char	**tmp_envi;
	char	**old_envi;

	if (arguments[0] == NULL || arguments[1] != NULL)
	{
		ft_putendl(WN_UNSETENV);
		return ;
	}
	old_envi = *envi;
	if (ft_strequ(*arguments, "PATH"))
		free_bins(bins);
	tmp_envi = *envi;
	new_envi = get_envi_array(tmp_envi, -1);
	envi_head = new_envi;
	while (*tmp_envi != NULL)
	{
		if (ft_strstr(*tmp_envi, *arguments) == NULL)
			*envi_head++ = ft_strdup(*tmp_envi++);
		else
			++tmp_envi;
	}
	free_envi_array(old_envi);
	*envi_head = NULL;
	*envi = new_envi;
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
