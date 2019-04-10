/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 16:30:06 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/10 12:40:03 by rgyles           ###   ########.fr       */
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

void	free_char_array(char ***arg)
{
	char		**array;

	if (*arg == NULL)
		return ;
	array = *arg;
	while (*array != NULL)
		free(*array++);
	free(*arg);
	*arg = NULL;
}

void	free_bins(t_bin **bins)
{
	t_bin	*tmp;
	t_bin	*head;

	if (*bins == NULL)
		return ;
	head = *bins;
	while (head != NULL)
	{
		free(head->dir);
		free_char_array(&head->bins);
		tmp = head;
		head = head->next;
		free(tmp);
	}
	*bins = NULL;
}
