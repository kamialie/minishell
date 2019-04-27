/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dollar_sign.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 19:42:38 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/11 13:24:19 by rgyles           ###   ########.fr       */
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
		value = ft_strchr(value, '=') + 1;
	free(field);
	return (value);
}

static int	total_str_len(t_list *head)
{
	int		total_len;

	total_len = 0;
	while (head != NULL)
	{
		total_len += head->content_size;
		head = head->next;
	}
	return (total_len);
}

static char	*cancat_arg(t_list *head)
{
	int		i;
	char	*str;
	char	*argument;
	t_list	*tmp;

	i = 0;
	tmp = head;
	argument = ft_strnew(total_str_len(head));
	while (head != NULL)
	{
		str = head->content;
		while (*str != '\0')
			argument[i++] = *str++;
		head = head->next;
	}
	free_list(&tmp);
	argument[i] = '\0';
	return (argument);
}

static void	add_pid(t_list **head)
{
	char	*pid;

	pid = ft_itoa(getpid());
	ft_lstadd(head, ft_lstnew(pid, ft_strlen(pid)));
}

void		check_dollar_sign(char **argument, char **envi)
{
	char	*p;
	char	*str;
	char	*value;
	t_list	*head;

	head = NULL;
	str = *argument;
	while ((p = ft_strchr(str, '$')))
	{
		if (p != str)
			ft_lstaddlast(&head, ft_lstnew(str, p - str));
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
		str = p;
	}
	free(*argument);
	*argument = cancat_arg(head);
}
