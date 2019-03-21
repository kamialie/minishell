/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:45:32 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/20 13:29:27 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s)
{
	int count;

	count = 0;
	while (*s != '\0')
	{
		while (*s == ' ' || *s == '\n' || *s == '\t')
			s++;
		if (*s == '\0')
			return (count);
		count++;
		while (*s != ' ' && *s != '\n' && *s != '\t' && *s != '\0')
			s++;
	}
	return (count);
}

static int	ft_count_letters(char *s)
{
	int count;

	count = 0;
	while (*s != '\0')
	{
		while (*s == ' ' || *s == '\n' || *s == '\t')
			s++;
		while (*s != ' ' && *s != '\n' && *s != '\t' && *s != '\0')
		{
			count++;
			s++;
		}
		return (count);
	}
	return (count);
}

static char	*ft_write_word(char **s)
{
	int		i;
	int		count;
	char	*word;

	i = 0;
	count = ft_count_letters(*s);
	if (!(word = (char *)malloc(sizeof(*word) * (count + 1))))
		return (NULL);
	while (i < count)
	{
		word[i] = *(*s);
		i++;
		(*s)++;
	}
	word[i] = '\0';
	return (word);
}

static void	ft_free(char ***array, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		free(*(array[i]));
		*(array[i]) = NULL;
		i++;
	}
	free(*array);
	*array = NULL;
}

char		**ft_split_whitespaces(char *s)
{
	int		i;
	int		count;
	char	**array;

	if (s == NULL)
		return (NULL);
	i = 0;
	count = ft_count_words(s);
	if (!(array = (char **)malloc(sizeof(*array) * (count + 1))))
		return (NULL);
	while (i < count)
	{
		while (*s != '\0' && (*s == ' ' || *s == '\n' || *s == '\t'))
			s++;
		if ((array[i] = ft_write_word(&s)) == NULL)
		{
			ft_free(&array, i);
			return (NULL);
		}
		i++;
	}
	array[i] = 0;
	return (array);
}
