/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_binaries.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 12:22:14 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/29 18:58:34 by rgyles           ###   ########.fr       */
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
	//struct dirent	*file;
	t_bin	*new;

	if (access(dir_path, F_OK) == 0)
	{
		new = (t_bin *)malloc(sizeof(*new));
		new->dir = dir_path;
		new->bins = get_binaries(dir_path);
		//printf("binary - %s\n", new->bins[0]);
		new->next = NULL;
		return (new);
	}
	return (NULL);
}

t_bin	*init_binaries(char *path)
{
	char	*dir_path;
	t_bin	*head;

	if (path == NULL)
		return (NULL);
	head = NULL;
	//printf("%s\n", path);
	dir_path = ft_strcsub(path, ':');
	//printf("%s\n", dir_path);
	path += ft_strlen(dir_path) + 1;
	while (*path != '\0')
	{
		dir_path = ft_strcsub(path, ':');
		push_back_bin(&head, get_new_bin(dir_path));
		//printf("%s\n", dir_path);
		path += ft_strlen(dir_path) + 1;
	}
	return (head);
}
