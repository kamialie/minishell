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

int	check_command(char *str)
{
	int		i;
	int		value;
	char	**command;

	i = -1;
	value = 0;
	command = ft_strsplit(str, ' ');
	if (ft_strequ(command[0], "exit"))
		value = 1;
	else
	{
		ft_putstr(N_FOUND);
		ft_putendl(command[0]);
	}
	while (command[++i] != NULL)
		free(command[i]);
	free(command);
	return (value);
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
		if (*str != '\0' && check_command(str))
			return (0);
		free(str);
		ft_putstr(O_YELLOW "minishell " O_NC);
	}
	return (0);
}
