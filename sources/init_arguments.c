/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arguments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 10:15:53 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/27 11:13:47 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*get_words(char *input)
{
	int		size;
	char	c;
	t_list	*head;

	head = NULL;
	while (*input != '\0')
	{
		c = *input;
		while (c == ' ' || c == '\t' || c == '\n')
			c = *++input;
		if (c == '\0')
			return (head);
		size = 0;
		c = input[size];
		while (c != ' ' && c != '\0' && c != '\n' && c != '\t')
			c = input[++size];
		ft_lstaddlast(&head, ft_lstnew(input, size));
		input += size;
	}
	return (head);
}

static void	free_list(t_list *head)
{
	t_list	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

char	**init_arguments(char *input)
{
	int		i;
	char	**arguments;
	t_list	*head;
	t_list	*tmp;

	head = get_words(input);
	arguments = (char **)malloc(sizeof(*arguments) * (ft_lstcount(head) + 1));
	tmp = head;
	i = -1;
	while (tmp != NULL)
	{
		arguments[++i] = tmp->content;
		tmp = tmp->next;
	}
	free_list(head);
	arguments[++i] = NULL;
	return (arguments);
}
