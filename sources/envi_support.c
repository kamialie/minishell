#include "minishell.h"

char	*join_envi_line(char *field, char *value)
{
	char	*line;
	char	*new;

	new = (char *)malloc(sizeof(*line) * (ft_strlen(field) + ft_strlen(value) + 2));
	line = new;
	while (*field != '\0')
		*new++ = *field++;
	*new++ = '=';
	while (*value != '\0')
		*new++ = *value++;
	*new = '\0';
	return (line);
}

int	find_envi_field(char *line, char *field)
{
	int	i;

	i = 0;
	while (line[i] == field[i])
		i++;
	if (field[i] == '\0' && line[i] == '=')
		return (1);
	return (0);
}

char	*get_envi_field(char *field, char **envi)
{
	while (*envi != NULL)
	{
		if (find_envi_field(*envi, field))
			return (*envi);
		++envi;
	}
	return (NULL);
}

void	update_envi_field(char *field, char *new_line, char ***envi)
{
	char	**new_envi;

	new_envi = *envi;
	while (*new_envi != NULL)
	{
		if (find_envi_field(*new_envi, field))
		{
			free(*new_envi);
			*new_envi = new_line;
			return ;
		}
		++new_envi;
	}
}
