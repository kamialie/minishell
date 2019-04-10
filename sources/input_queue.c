/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_queue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 16:19:25 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/10 14:49:42 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_command(char **arguments, char ***envi, t_bin **bins)
{
	if (**arguments == '/' || **arguments == '.')
		command_path(arguments, *envi);
	else if (ft_strequ(arguments[0], "echo"))
		echo(arguments + 1);
	else if (ft_strequ(arguments[0], "cd"))
		change_direct(arguments + 1, envi);
	else if (ft_strequ(arguments[0], "env"))
		print_envi(*(arguments + 1), *envi);
	else if (ft_strequ(arguments[0], "setenv"))
		set_envi(arguments + 1, envi, bins);
	else if (ft_strequ(arguments[0], "unsetenv"))
		unset_envi(arguments + 1, envi, bins);
	else
		command(arguments, *envi, *bins);
}

void		form_request(char *str, char ***envi, t_bin **bins)
{
	char	**arguments;

	if ((arguments = init_arguments(str, *envi)) != NULL)
	{
		exec_command(arguments, envi, bins);
		free_char_array(&arguments);
	}
}

void		command_queue(char *input, char ***envi, t_bin **bins)
{
	int		i;
	char	**commands;

	commands = ft_strsplit(input, ';');
	i = -1;
	while (commands[++i] != NULL)
		form_request(commands[i], envi, bins);
	free_char_array(&commands);
}
