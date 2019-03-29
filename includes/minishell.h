/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 19:25:50 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/29 14:10:06 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <sys/stat.h>
# include <stdio.h>
# include <dirent.h>

# define O_YELLOW "\033[01;33m"
# define O_NC "\033[0m"

# define SHELL "minishell: "
# define CD "cd: "

# define NF_COMMAND SHELL "command not found: "
# define NF_FOD "no such file or directory: "

# define NF_HD_CD CD "home directory not found"
# define NF_OLDPWD_CD CD "old pwd not found"
# define NF_FOD_CD CD NF_FOD

# define ER_CD CD "error"
# define ND_CD CD "not a directory: "
# define TMA_CD CD "too many arguments"

typedef struct	s_bin
{
	char			*dir;
	char			**bins;
	struct s_bin	*next;
}				t_bin;

char	**init_arguments(char *input);

char	**init_environment(char **environ);
char	**get_envi_array(char **envi, int flag);
void	free_envi_array(char **envi);
void	print_envi(char *str, char **envi);
char	**set_envi(char **arguments, char **envi);
char	**unset_envi(char **arguments, char **envi);
char	*get_envi_field(char *field, char **envi);
void	update_envi_field(char *field, char *new_line, char ***envi);

t_bin	*init_binaries(char *path);

void	change_direct(char **arguments, char ***envi);

void	echo(char **arguments);
void	command(char **arguments, char **envi);

#endif
