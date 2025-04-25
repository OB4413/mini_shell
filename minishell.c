/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:56:34 by obarais           #+#    #+#             */
/*   Updated: 2025/04/25 19:36:01 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char	*line;
	t_input	*tok;

	while(1)
	{
		line = readline("minishell$ ");

		if (!line)
			return(printf("Exiting...\n"), 0);
		if (strlen(line) > 0)
		{
			add_history(line);

			tokenization(line, &tok);

			pid_t pid = fork();
            if (pid == 0)
                exit(1);
            else
				wait(&pid);
		}
	}
}
