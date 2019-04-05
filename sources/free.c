/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 16:30:06 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/05 16:12:51 by rgyles           ###   ########.fr       */
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

void	free_char_array(char **array)
{
	int		i;

	i = -1;
	while (array[++i] != NULL)
		free(array[i]);
	free(array);
}

void	free_bins(t_bin **bins)
{
	t_bin	*tmp;
	t_bin	*head;

	head = *bins;
	while (head != NULL)
	{
		free_char_array(head->bins);
		tmp = head;
		head = head->next;
		free(tmp);
	}
	*bins = NULL;
}
