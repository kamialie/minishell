/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 18:30:54 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/09 10:25:28 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_envi_value(char **argument, char **envi)
{
	int		len;
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
	return (value);
}

static char	*cancat_arg(t_list *head)
{
	int		i;
	int		total_len;
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

static void	add_pid(t_list **head)
{
	char	*pid;

	pid = ft_itoa(getpid());
	ft_lstadd(head, ft_lstnew(pid, ft_strlen(pid)));
}

static char	*check_dollar_sign(char *argument, char **envi)
{
	char	*p;
	char	*str;
	char	*value;
	t_list	*head;

	head = NULL;
	str = argument;
	while ((p = ft_strchr(argument, '$')))
	{
		if (p != argument)
			ft_lstaddlast(&head, ft_lstnew(argument, p - argument));
		if (*++p == '$')
		{
			add_pid(&head);
			++p;
		}
		else if (ft_isalnum(*p))
		{
			if ((value = get_envi_value(&p, envi)) != NULL)
				ft_lstaddlast(&head, ft_lstnew(value, ft_strlen(value)));
		}
		argument = p;
	}
	free(str);
	return (cancat_arg(head));
}

char		*check_argument(char *argument, char **envi)
{
	char	*str;
	char	*home;

	if (ft_strchr(argument, '$'))
		argument = check_dollar_sign(argument, envi);
	if (*argument == '~')
	{
		if (*(argument + 1) != '\0' && *(argument + 1) != '/')
		{
			ft_putstr(NUD_SH);
			str = ft_strdup(argument + 1);
		}
		else
		{
			home = get_envi_field("HOME", envi);
			str = ft_strjoin(home + 5, argument + 1);
		}
		free(argument);
		argument = str;
	}
	return (argument);
}
