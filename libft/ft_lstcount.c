/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 12:59:47 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/07 16:32:19 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstcount(t_list *begin_list)
{
	int		count;
	t_list	*cur;

	count = 1;
	cur = begin_list;
	if (begin_list == NULL)
		return (0);
	while (cur->next != NULL)
	{
		cur = cur->next;
		count++;
	}
	return (count);
}
