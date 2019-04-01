#include "minishell.h"

static t_list	*sub_envi_var(char *argument, char **envi)
{
	int	len;
	char	*field;
	char	*value;
	t_list	*new;

	len = 0;
	while (ft_isalnum(argument[len]))
		++len;
	field = ft_strsub(argument, 0, len);
	if ((value = get_envi_field(field, envi)) != NULL)
	{
		value = ft_strchr(value, '=') + 1;
		new = ft_lstnew(value, ft_strlen(value));
	}
	else
		new = ft_lstnew("", 1);
	free(field);
	return (new);
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

char	*check_argument(char *argument, char **envi)
{
	int	i;
	char	*field;
	t_list	*head;

	i = -1;
	head = NULL;
	if (argument[i] == '~' && (argument[i] == '\0' || argument[i] == '/'
			|| (argument[i] == '$' && argument[i + 1] != '\0')))
		ft_lstaddlast(&head, ft_lstnew(
	if ((value = get_envi_field(field, envi)) != NULL)
	while (argument[++i] != '\0')
	{
		if (argument[i] == '$')
		{
			ft_lstaddlast(&head, ft_lstnew(argument, i));
			ft_lstaddlast(&head, sub_envi_var(argument + i + 1, envi));
		}
	}
	if (head)
		return (cancat_arg(head));
	return (argument);
}
