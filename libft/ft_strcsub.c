/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 12:45:28 by rgyles            #+#    #+#             */
/*   Updated: 2018/12/02 18:44:12 by rgyles           ###   ########.fr       */
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
	while (*s != c)
		*str++ = *s++;
	*str = '\0';
	return (str);
}
