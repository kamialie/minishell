/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_binaries.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 12:22:14 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/08 14:11:08 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push_back_bin(t_bin **head, t_bin *new)
{
	t_bin	*tmp;

	tmp = *head;
	if (new == NULL)
		return ;
	if (tmp == NULL)
		*head = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

char	**join_bin_array(t_list *head)
{
	int		i;
	int		count;
	char	**bin_array;
	t_list	*tmp;

	i = 0;
	count = ft_lstcount(head);
	bin_array = (char **)malloc(sizeof(*bin_array) * ++count);
	while (head != NULL)
	{
		bin_array[i++] = head->content;
		tmp = head;
		free(tmp);
		head = head->next;
	}
	bin_array[i] = NULL;
	return (bin_array);
}

char	**get_binaries(char *dir_path)
{
	DIR				*dir;
	char			*file_path;
	struct dirent	*file;
	t_list			*head;

	head = NULL;
	dir = opendir(dir_path);
	while ((file = readdir(dir)))
	{
		file_path = ft_strjoin_mid(dir_path, file->d_name, '/');
		if (access(file_path, X_OK) == 0 && *file->d_name != '.')
			ft_lstadd(&head, ft_lstnew(file->d_name, ft_strlen(file->d_name)));
	}
	closedir(dir);
	return (join_bin_array(head));
}

t_bin	*get_bin_direct(char *dir_path)
{
	t_bin	*new;

	if (access(dir_path, F_OK) == 0)
	{
		new = (t_bin *)malloc(sizeof(*new));
		new->dir = dir_path;
		new->bins = get_binaries(dir_path);
		new->next = NULL;
		return (new);
	}
	return (NULL);
}

void	init_binaries(char *path, t_bin **bins)
{
	int		i;
	char	**dir;
	t_bin	*head;

	if (path == NULL)
		return ;
	if (*bins != NULL)
		free_bins(bins);
	head = NULL;
	if (ft_strchr(path, ':'))
	{
		i = 0;
		dir = ft_strsplit(path, ':');
		while (dir[i] != NULL)
		{
			push_back_bin(&head, get_bin_direct(dir[i]));
			i++;
		}
		free_char_array(&dir);
	}
	else
		push_back_bin(&head, get_bin_direct(path));
	*bins = head;
}
