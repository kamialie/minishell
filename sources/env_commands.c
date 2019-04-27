/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:59:28 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/11 13:12:03 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		set_envi(char **arguments, char ***envi, t_bin **bins)
{
	char	**new_envi;
	char	**tmp_envi;
	char	**old_envi;

	if (arguments[0] == NULL || arguments[1] == NULL || arguments[2] != NULL)
		ft_putendl(WN_SETENV);
	else
	{
		if ((update_envi_field(*arguments, *(arguments + 1), envi)) == 0)
		{
			new_envi = get_envi_array(*envi, 1);
			old_envi = *envi;
			tmp_envi = new_envi;
			while (*old_envi != NULL)
				*tmp_envi++ = ft_strdup(*old_envi++);
			free_char_array(envi);
			*tmp_envi = join_envi_line(*arguments, *(arguments + 1));
			*envi = new_envi;
		}
		if (ft_strequ(*arguments, "PATH"))
		{
			free_bins(bins);
			init_binaries(get_envi_field("PATH", *envi) + 5, bins);
		}
	}
}

static void	envi_copy_back(char **arguments, char ***envi)
{
	char	**new_envi;
	char	**envi_head;
	char	**tmp_envi;
	char	**old_envi;

	tmp_envi = *envi;
	old_envi = *envi;
	new_envi = get_envi_array(tmp_envi, -1);
	envi_head = new_envi;
	while (*tmp_envi != NULL)
	{
		if (ft_strstr(*tmp_envi, *arguments) == NULL)
			*envi_head++ = ft_strdup(*tmp_envi++);
		else
			++tmp_envi;
	}
	free_char_array(&old_envi);
	*envi = new_envi;
}

void		unset_envi(char **arguments, char ***envi, t_bin **bins)
{
	if (arguments[0] == NULL || arguments[1] != NULL)
	{
		ft_putendl(WN_UNSETENV);
		return ;
	}
	if (ft_strequ(*arguments, "PATH"))
		free_bins(bins);
	if (get_envi_field(arguments[0], *envi) != NULL)
		envi_copy_back(arguments, envi);
}

void		print_envi(char *str, char **envi)
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
