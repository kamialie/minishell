/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 19:25:50 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/20 16:12:51 by rgyles           ###   ########.fr       */
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
# define I_PWD "pwd: too many arguments"

char	**init_environment(char **environ);
void	echo(char **arguments);
void	pwd(char *str, char **environ);
void	env(char *str, char **environ);

#endif
