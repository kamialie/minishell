/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 16:11:50 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/21 15:19:11 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_envi(t_envi *head)
{
	t_envi	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

void		unset_envi(char *str, t_envi **head)
{
	t_envi	*tmp;
	t_envi	*current;

	current = *head;
	if (ft_strstr(current->field, str))
	{
		*head = (*head)->next;
		free(current);
	}
	else
	{
		tmp = current;
		current = current->next;
		while (current != NULL)
		{
			if (ft_strstr(current->field, str))
			{
				tmp->next = current->next;
				return ;
			}
			tmp = current;
			current = current->next;
		}
	}
}

static void	push_back_envi_field(t_envi **head, char *field, char *value)
{
	t_envi	*new;
	t_envi	*tmp;

	new = (t_envi *)malloc(sizeof(*new));
	new->field = field;
	new->value = value;
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_envi	*init_environment(char **environ)
{
	char	*p;
	char	*field;
	char	*value;
	t_envi	*head;

	head = NULL;
	while (*environ != NULL)
	{
		p = ft_strchr(*environ, '=');
		field = ft_strsub(*environ, 0, ++p - *environ);
		if (ft_strstr(*environ, "SHELL"))
			value = getcwd(NULL, 0); //need full path to binary
		else if (ft_strstr(*environ, "SHLVL"))
			value = ft_itoa(ft_atoi(*environ + 6) + 1);
		else
			value = ft_strsub(p, 0, ft_strlen(p));
		push_back_envi_field(&head, field, value);
		++environ;
	}
	return (head);
}
