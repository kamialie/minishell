/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 19:25:50 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/26 17:31:55 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>

# define O_YELLOW "\033[01;33m"
# define O_NC "\033[0m"

# define SHELL "minishell: "
# define NF_COMMAND SHELL "command not found: "
# define NF_FOD ": No such file or directory"

# define NF_HD SHELL "cd: home directory not found"
# define NF_OLDPWD SHELL "cd: old pwd not found"

# define ER_CD SHELL "cd: error"

char	**init_environment(char **environ);
char	**get_envi_array(char **envi, int flag);
char	*get_envi_field(char *field, char **envi);
void	free_envi_array(char **envi);
void	print_envi(char *str, char **envi);
char	**set_envi(char **arguments, char **envi);
char	**unset_envi(char **arguments, char **envi);

char	**change_direct(char **arguments, char **envi);

void	echo(char **arguments);
void	command(char **arguments, char **envi);

#endif
