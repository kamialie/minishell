/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 19:24:32 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/06 13:20:47 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static int	control = 1;

int		check_command(char **arguments, char ***envi, t_bin **bins)
{
	int	exit;

	exit = 0;
	if (**arguments == '/' || **arguments == '.')
		command_path(arguments, *envi);
	else if (ft_strequ(arguments[0], "exit"))
		exit = 1;
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
	free_char_array(arguments);
	return (exit);
}

void	input_queue(char ***my_envi, t_bin **bins)
{
	int		i;
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*str;
	char	**command_queue;

	ft_putstr(O_YELLOW "minishell " O_NC);
	while ((ret = read(0, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		i = -1;
		command_queue = ft_strsplit(buf, ';');
		while (command_queue[++i] != NULL)
		{
			str = ft_strtrim(command_queue[i]);
			if (*str != '\0' && check_command(init_arguments(str, *my_envi), my_envi, bins))
			{
				free(command_queue);
				free(str);
				return ;
			}
			free(str);
		}
		free(command_queue);
		ft_putstr(O_YELLOW "minishell " O_NC);
	}
}

//void	handle_sig(int sig)
//{
	//sig = 0;
	//control = 1;
	////signal(SIGINT, handle_sig);
	//write(1, "\n", 1);
	//ft_putstr(O_YELLOW "minishell " O_NC);
//}

int		main(int args, char **argv, char **environ)
{
	char	**my_envi;
	t_bin	*bins;

	(void)args;
	(void)argv;
	bins = NULL;
	my_envi = init_environment(environ);
	init_binaries(get_envi_field("PATH", my_envi) + 5, &bins);
	//signal(SIGINT, handle_sig);
	input_queue(&my_envi, &bins);
	free_bins(&bins);
	free_char_array(my_envi);
	return (0);
}
