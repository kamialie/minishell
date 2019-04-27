/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envi_support.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 12:19:54 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/10 19:29:39 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*join_envi_line(char *field, char *value)
{
	char	*line;
	char	*new;

	new = (char *)malloc(sizeof(*line) *
		(ft_strlen(field) + ft_strlen(value) + 2));
	line = new;
	while (*field != '\0')
		*new++ = *field++;
	*new++ = '=';
	while (*value != '\0')
		*new++ = *value++;
	*new = '\0';
	return (line);
}

static int	confirm_envi_field(char *line, char *field)
{
	int	i;

	i = 0;
	while (line[i] == field[i])
		i++;
	if (field[i] == '\0' && line[i] == '=')
		return (1);
	return (0);
}

char		*get_envi_field(char *field, char **envi)
{
	while (*envi != NULL)
	{
		if (confirm_envi_field(*envi, field))
			return (*envi);
		++envi;
	}
	return (NULL);
}

int			update_envi_field(char *field, char *new_line, char ***envi)
{
	char	**new_envi;

	new_envi = *envi;
	while (*new_envi != NULL)
	{
		if (confirm_envi_field(*new_envi, field))
		{
			free(*new_envi);
			*new_envi = join_envi_line(field, new_line);
			return (1);
		}
		++new_envi;
	}
	return (0);
}
