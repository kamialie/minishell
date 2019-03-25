/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 19:25:50 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/25 17:30:19 by rgyles           ###   ########.fr       */
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

typedef struct	s_envi
{
	char		*field;
	char		*value;
	struct s_envi	*next;
}		t_envi;

t_envi	*init_environment(char **environ);
void	free_envi(t_envi *head);
void	env(char *str, t_envi *head);
void	unset_envi(char *str, t_envi **head);

void	echo(char **arguments);
void	pwd(char *str, char **environ);
void	command(char **commands, char **my_env);

#endif
