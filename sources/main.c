/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 19:24:32 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/27 11:13:57 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arguments(char **arguments)
{
	int		i;

	i = -1;
	while (arguments[++i] != NULL)
		free(arguments[i]);
	free(arguments);
}

int		check_command(char **arguments, char ***envi)
{
	//while (*arguments != NULL)
	//{
		//ft_putendl(*arguments);
		//++arguments;
	//}
	if (ft_strequ(arguments[0], "exit"))
	{
		free_arguments(arguments);
		return (1);
	}
	else if (ft_strequ(arguments[0], "echo"))
		echo(arguments + 1);
	else if (ft_strequ(arguments[0], "cd"))
		change_direct(arguments + 1, envi);
	else if (ft_strequ(arguments[0], "env"))
		print_envi(*(arguments + 1), *envi);
	else if (ft_strequ(arguments[0], "setenv"))
		*envi = set_envi(arguments + 1, *envi);
	else if (ft_strequ(arguments[0], "unsetenv"))
		*envi = unset_envi(arguments + 1, *envi);
	else
	{
		command(arguments, *envi);
		//ft_putstr(NF_COMMAND);
		//ft_putendl(arguments[0]);
	}
	if (*envi == NULL)
		ft_putendl("error while set/unset env variable");
	free_arguments(arguments);
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
		if (*str != '\0' && check_command(init_arguments(str), &my_env))
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
