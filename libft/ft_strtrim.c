/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 13:05:54 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/19 17:37:08 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_length_trim(char const *s)
{
	size_t	i;
	size_t	end;

	i = 0;
	end = 0;
	while (*s == ' ' || *s == '\n' || *s == '\t')
		s++;
	while (s[i] != '\0')
	{
		while (s[i] != ' ' && s[i] != '\n' && s[i] != '\t' && s[i] != '\0')
			i++;
		end = i;
		while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
			i++;
	}
	return (end);
}

char		*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*str;

	if (s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	len = ft_length_trim(s);
	if (!(str = (char *)malloc(sizeof(*str) * (len + 1))))
		return (NULL);
	while (s[j] == ' ' || s[j] == '\n' || s[j] == '\t')
		j++;
	while (i < len)
		str[i++] = s[j++];
	str[i] = '\0';
	return (str);
}
