/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 18:30:54 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/10 20:43:11 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_home_dir(char **argument, char **envi)
{
	char	*str;
	char	*home;

	str = *argument;
	if (str[1] != '\0' && str[1] != '/')
	{
		ft_putstr(NUD_SH);
		str = ft_strdup(*argument + 1);
	}
	else
	{
		home = get_envi_field("HOME", envi);
		str = ft_strjoin(home + 5, *argument + 1);
	}
	free(*argument);
	*argument = str;
}

void		check_argument(char **argument, char **envi)
{
	if (ft_strchr(*argument, '$'))
		check_dollar_sign(argument, envi);
	if (**argument == '~')
		add_home_dir(argument, envi);
}
