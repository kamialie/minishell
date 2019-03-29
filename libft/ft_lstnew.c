/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 16:23:23 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/29 13:35:24 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_write_word(char *str, size_t content_size)
{
	size_t	i;
	char	*s;

	i = 0;
	if (str == NULL || !(s = (char *)malloc(sizeof(*s) * content_size)))
		return (NULL);
	while (i < content_size)
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*p;

	if (!(p = (t_list *)malloc(sizeof(*p))))
		return (NULL);
	p->content = ft_write_word((char*)content, content_size);
	if (content == NULL)
		p->content_size = 0;
	else
		p->content_size = content_size;
	p->next = NULL;
	return (p);
}
