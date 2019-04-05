/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 19:24:32 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/05 13:52:19 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	control = 1;

int		check_command(char **arguments, char ***envi, t_bin **bins)
{
	if (**arguments == '/' || **arguments == '.')
		command_path(arguments, *envi);
	else if (ft_strequ(arguments[0], "exit"))
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
		set_envi(arguments + 1, envi, bins);
	else if (ft_strequ(arguments[0], "unsetenv"))
		unset_envi(arguments + 1, envi, bins);
	else
		command(arguments, *envi, *bins);
	free_arguments(arguments);
	return (0);
}

void	handle_sig(int sig)
{
	sig = 0;
	control = 1;
	signal(SIGINT, handle_sig);
	write(1, "\n", 1);
	ft_putstr(O_YELLOW "minishell " O_NC);
}
	
int		main(int args, char **argv, char **environ)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*str;
	char	**my_envi;
	t_bin	*bins;

	(void)args;
	(void)argv;
	bins = NULL;
	my_envi = init_environment(environ);
	init_binaries(get_envi_field("PATH", my_envi) + 5, &bins);
	//TMP OUTPUT
	//head = bins;
	//while (head != NULL)
	//{
		//i = 0;
		//printf("dir - %s\n\n", head->dir);
		//while (head->bins[i] != NULL)
		//{
			//printf("binary  - %s\n", head->bins[i]);
			//++i;
		//}
		//head = head->next;
	//}
	//END
	signal(SIGINT, handle_sig);
	ft_putstr(O_YELLOW "minishell " O_NC);
	while ((ret = read(0, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		str = ft_strtrim(buf);
		if (*str != '\0' && check_command(init_arguments(str, my_envi), &my_envi, &bins))
		{
			free_bins(&bins);
			free_envi_array(my_envi);
			free(str);
			return (0);
		}
		free(str);
		ft_putstr(O_YELLOW "minishell " O_NC);
	}
	return (0);
}
