/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 19:24:32 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/10 16:15:26 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	g_control = 1;

static void	handle_sig(int sig)
{
	sig = 0;
	signal(SIGINT, handle_sig);
	write(1, "\n", 1);
	//ft_putstr(O_YELLOW "minishell " O_NC);
	g_control = 0;
}

static int	input_queue(char ***envi, t_bin **bins)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*str;
	char	*p;

	if ((ret = read(0, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		p = ft_strstr(buf, "exit");
		if (p != NULL && ft_isalnum(*(p + 4)) == 0)
			return (0);
		str = ft_strtrim(buf);
		if (*str != '\0')
		{
			if (ft_strchr(str, ';') == NULL)
				form_request(str, envi, bins);
			else
				command_queue(str, envi, bins);
		}
		free(str);
	}
	return (1);
}

int			main(int args, char **argv, char **environ)
{
	char	**my_envi;
	t_bin	*bins;

	(void)args;
	bins = NULL;
	my_envi = init_environment(*argv, environ);
	init_binaries(get_envi_field("PATH", my_envi) + 5, &bins);
	ft_putstr(O_YELLOW "minishell " O_NC);
	signal(SIGINT, handle_sig);
	while (input_queue(&my_envi, &bins))
	{
		if (g_control)
			ft_putstr(O_YELLOW "minishell " O_NC);
		g_control = 1;
	}
	free_bins(&bins);
	free_char_array(&my_envi);
	return (0);
}
