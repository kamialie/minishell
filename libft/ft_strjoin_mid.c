/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_mid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 13:16:23 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/29 14:15:31 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_mid(char *s1, char *s2, char c)
{
	char	*line;
	char	*new;

	new = (char *)malloc(sizeof(*line) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	line = new;
	while (*s1 != '\0')
		*new++ = *s1++;
	*new++ = c;
	while (*s2 != '\0')
		*new++ = *s2++;
	*new = '\0';
	return (line);
}
