/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 18:30:54 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/03 20:25:56 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_envi_value(char **argument, char **envi)
{
	int	len;
	char	*p;
	char	*field;
	char	*value;

	len = 0;
	p = *argument;
	while (ft_isalnum(p[len]))
		++len;
	field = ft_strsub(p, 0, len);
	*argument = p + len;
	if ((value = get_envi_field(field, envi)) != NULL)
	{
		value = ft_strchr(value, '=') + 1;
		value = ft_strdup(value);
	}
	else
		value = ft_strnew(1);
	return (value);
}

char	*cancat_arg(t_list *head)
{
	int	i;
	int	total_len;
	char	*str;
	char	*argument;
	t_list	*tmp_head;

	i = 0;
	total_len = 0;
	tmp_head = head;
	while (tmp_head != NULL)
	{
		total_len += tmp_head->content_size;
		tmp_head = tmp_head->next;
	}
	argument = ft_strnew(total_len);
	while (head != NULL)
	{
		str = head->content;
		while (*str != '\0')
			argument[i++] = *str++;
		head = head->next;
	}
	argument[i] = '\0';
	return (argument);
}

/*char	*check_argument(char *argument, char **envi)
{
	int	i;
	char	*value;
	t_list	*head;

	i = 0;
	head = NULL;
	if (argument[i] == '~' && (argument[i + 1] == '\0' || argument[i + 1] == '/'
			|| (argument[i + 1] == '$' && argument[i + 2] != '\0')))
	{
		if ((value = get_envi_field("HOME", envi)) != NULL)
			ft_lstaddlast(&head, ft_lstnew(value + 5, ft_strlen(value + 5)));
		++argument;
	}
	while (argument[i] != '\0')
	{
		if (argument[i] == '$')
		{
			ft_lstaddlast(&head, ft_lstnew(argument, i));
			ft_lstaddlast(&head, sub_envi_var(argument + i + 1, envi));
		}
		++i;
	}
	if (head)
		return (cancat_arg(head));
	return (argument);
}*/

char	*check_argument(char *argument, char **envi)
{
	char	*p;
	char	*str;
	char	*value;
	char	*home;
	t_list	*head;

	head = NULL;
	str = argument;
	while ((p = ft_strchr(argument, '$')) != NULL)
	{
		if (p != argument)
			ft_lstaddlast(&head, ft_lstnew(argument, p - argument));
		++p;
		value = get_envi_value(&p, envi);
		ft_lstaddlast(&head, ft_lstnew(value, ft_strlen(value)));
		argument = p;
		if (*value == '\0')
			break ;
	}
	if (head != NULL)
	{
		if (*argument != '\0')
			ft_lstaddlast(&head, ft_lstnew(argument, ft_strlen(argument)));
		free(str);
		argument = cancat_arg(head);
	}
	if (*argument == '~')
	{
		argument++;
		if (*argument != '\0' && *argument != '/')
		{
			free(argument);
			return (NULL);
		}
		home = get_envi_field("HOME", envi);
		str = ft_strjoin(home + 5, argument + 1);
		free(argument);
		argument = str;
	}
	return (argument);
}
