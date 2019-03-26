/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 19:25:50 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/26 11:50:07 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>

# define O_YELLOW "\033[01;33m"
# define O_NC "\033[0m"

# define N_FOUND "minishell: command not found: "

char	**init_environment(char **environ);
char	**get_envi_array(char **envi, int flag);
void	free_envi_array(char **envi);
void	print_envi(char *str, char **envi);
char	**set_envi(char **arguments, char **envi);
char	**unset_envi(char **arguments, char **envi);

void	echo(char **arguments);
void	pwd(char *str, char **environ);
void	command(char **commands, char **my_env);

#endif
