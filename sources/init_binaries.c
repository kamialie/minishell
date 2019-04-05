/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_binaries.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 12:22:14 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/05 12:56:32 by rgyles           ###   ########.fr       */
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

char	**get_binaries(char *dir_path)
{
	DIR				*dir;
	char			**new;
	int				count;
	char			*file_path;
	char			**bin_array;
	struct dirent	*file;
	t_list			*head;
	t_list			*tmp;

	head = NULL;
	count = 0;
	dir = opendir(dir_path);
	while ((file = readdir(dir)))
	{
		file_path = ft_strjoin_mid(dir_path, file->d_name, '/');
		if (access(file_path, X_OK) == 0 && *file->d_name != '.')
			ft_lstadd(&head, ft_lstnew(file->d_name, ft_strlen(file->d_name)));
	}
	closedir(dir);
	count = ft_lstcount(head);
	bin_array = (char **)malloc(sizeof(*bin_array) * ++count);
	new = bin_array;
	while (head != NULL)
	{
		*new++ = head->content;
		tmp = head;
		free(tmp);
		head = head->next;
	}
	*new = NULL;
	return (bin_array);
}

t_bin	*get_new_bin(char *dir_path)
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
	char	*dir_path;
	t_bin	*head;

	if (path == NULL)
		return ;
	if (*bins != NULL)
		free_bins(bins);
	head = NULL;
	dir_path = ft_strcsub(path, ':');
	path += ft_strlen(dir_path) + 1;
	while (*path != '\0')
	{
		if (ft_strchr(path, ':'))
		if ((dir_path = ft_strcsub(path, ':')) == NULL)
			dir_path = ft_strdup(path);
		push_back_bin(&head, get_new_bin(dir_path));
		path += ft_strlen(dir_path) + 1;
	}
	*bins = head;
}
