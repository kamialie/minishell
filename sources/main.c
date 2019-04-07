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
	free_char_array(&my_envi);
	return (0);
}
