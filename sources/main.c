/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 19:24:32 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/18 20:00:29 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];

	ft_putstr(O_YELLOW "minishell " O_NC);
	while ((ret = read(0, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		//ft_putstr(buf);
		if (ft_strequ(buf, "exit\n"))
			return (0);
		else
			ft_putstr(O_YELLOW "minishell " O_NC);
	}
	return (0);
}
