/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 16:30:06 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/29 16:30:28 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_struct(void *content, size_t len)
{
	free(content);
	len = 0;
}

void	free_envi_array(char **envi)
{
	int	i;

	i = -1;
	while (envi[++i] != NULL)
		free(envi[i]);
	free(envi);
}

void	free_arguments(char **arguments)
{
	int		i;

	i = -1;
	while (arguments[++i] != NULL)
		free(arguments[i]);
	free(arguments);
}
