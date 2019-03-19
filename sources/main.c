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

void	not_found(char *str)
{
	ft_putstr(N_FOUND);
	while (*str != '\0' && *str != '\n' && *str != '\t' && *str != ' ')
		write(1, str++, 1);
	ft_putstr("\n" O_YELLOW "minishell " O_NC);
}

int	check_command(char *str)
{
	int		i;
	int		value;
	char	**command;

	i = -1;
	command = ft_strsplit(str, ' ');
	free(str);
	if (ft_strequ(command[0], "exit"))
		value = 1;
	else if (ft_strequ(command[0], "echo"))
		value = 2;
	else
	{
		ft_putstr(command[0]);
		value = 0;
	}
	while (command[++i] != NULL)
		free(command[i]);
	free(command);
	return (value);
}

int	main(void)
{
	int		i;
	int		value;
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*str;

	ft_putstr(O_YELLOW "minishell " O_NC);
	while ((ret = read(0, buf, BUFF_SIZE)))
	{
		i = 0;
		buf[ret] = '\0';
		while (buf[i] != '\0' && buf[i] == '\t' && buf[i] == ' ' && buf[i] == '\n')
			i++;
		if (buf[i] != '\0')
		{
			str = ft_strtrim(buf);
			if ((value = check_command(str)))
			{
				if (value == 1)
					return (0);
			}
			else
				ft_putstr(N_FOUND);
		}
		ft_putstr(O_YELLOW "minishell " O_NC);
	}
	return (0);
}
