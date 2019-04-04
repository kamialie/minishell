/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 16:30:06 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/04 12:39:02 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_list **list)
{
	t_list	*tmp;
	t_list	*head;

	head = *list;
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->content);
		free(tmp);
	}
	*list = NULL;
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

void	free_bins(t_bin **bins)
{
	t_bin	*tmp;
	t_bin	*head;

	head = *bins;
	while (head != NULL)
	{
		free_arguments(head->bins);
		tmp = head;
		head = head->next;
		free(tmp);
	}
	*bins = NULL;
}
