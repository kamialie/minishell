/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 19:24:32 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/19 17:56:47 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_commands(char **commands)
{
	int		i;

	i = -1;
	while (commands[++i] != NULL)
		free(commands[i]);
	free(commands);
}

int	check_command(char **commands)
{
	if (ft_strequ(commands[0], "exit"))
	{
		free_commands(commands);
		return (1);
	}
	else
	{
		ft_putstr(N_FOUND);
		ft_putendl(commands[0]);
	}
	free_commands(commands);
	return (0);
}

int	main(void)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*str;

	ft_putstr(O_YELLOW "minishell " O_NC);
	while ((ret = read(0, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		str = ft_strtrim(buf);
		if (*str != '\0' && check_command(ft_strsplit(str, ' ')))
			return (0);
		free(str);
		ft_putstr(O_YELLOW "minishell " O_NC);
	}
	return (0);
}
