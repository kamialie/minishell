/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 19:24:32 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/26 11:58:28 by rgyles           ###   ########.fr       */
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

int		check_command(char **commands, char ***envi)
{
	if (ft_strequ(commands[0], "exit"))
	{
		free_commands(commands);
		return (1);
	}
	else if (ft_strequ(commands[0], "echo"))
		echo(commands + 1);
	else if (ft_strequ(commands[0], "env"))
		print_envi(*(commands + 1), *envi);
	else if (ft_strequ(commands[0], "setenv"))
		*envi = set_envi(commands, *envi);
	else if (ft_strequ(commands[0], "unsetenv"))
		*envi = unset_envi(commands, *envi);
	else
	{
		//command(commands, my_env);
		//ft_putstr(N_FOUND);
		//ft_putendl(commands[0]);
	}
	if (*envi == NULL)
		ft_putendl("error while set/unset env variable");
	free_commands(commands);
	return (0);
}

int		main(int args, char **argv, char **environ)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*str;
	char	**my_env;

	(void)args;
	(void)argv;
	my_env = init_environment(environ);
	ft_putstr(O_YELLOW "minishell " O_NC);
	while ((ret = read(0, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		str = ft_strtrim(buf);
		if (*str != '\0' && check_command(ft_split_whitespaces(str), &my_env))
		{
			free_envi_array(my_env);
			free(str);
			return (0);
		}
		free(str);
		ft_putstr(O_YELLOW "minishell " O_NC);
	}
	return (0);
}
