/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:56:27 by obarais           #+#    #+#             */
/*   Updated: 2025/04/26 19:47:14 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINI_SHELL_H
# define MINI_SHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>

typedef enum e_input_type
{
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC,
}					t_input_type;

typedef struct s_input
{
	char			*value;
	t_input_type	type;
	struct s_input	*next;
}					t_input;

typedef struct s_list_env
{
	char			*key;
	char			*value;
	struct s_list_env	*next;
}					list_env;

void	tokenization(char *line, t_input **tok);
void	expand_variables(t_input **tok, list_env *env);

#endif
