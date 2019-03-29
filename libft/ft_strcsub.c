/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 12:45:28 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/29 14:37:03 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcsub(char const *s, int c)
{
	char	*str;
	char	*p;

	if (s == NULL)
		return (NULL);
	if ((p = ft_strchr(s, c)) == NULL)
		return (ft_strdup(s));
	if (!(str = (char *)malloc(sizeof(*str) * (p - s + 1))))
		return (NULL);
	p = str;
	while (*s != c)
		*p++ = *s++;
	*p = '\0';
	return (str);
}
