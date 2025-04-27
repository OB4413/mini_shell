/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:56:34 by obarais           #+#    #+#             */
/*   Updated: 2025/04/27 07:52:23 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_list_env(char **env, list_env **env_list)
{
	int i;
	int j;
	list_env *new_env;
	list_env *tmp;

	i = 0;
	j = 0;
	while (env[i])
    {
        j = 0;
        while (env[i][j] != '=')
            j++;
        new_env = (list_env *)malloc(sizeof(list_env));
        if (!new_env)
            return ;
        new_env->key = ft_substr(env[i], 0, j);
        new_env->value = ft_substr(env[i], j + 1, ft_strlen(env[i]) - j);
        new_env->next = NULL;
        if (i == 0)
            *env_list = new_env;
        else
        {
            tmp = *env_list;
            while (tmp->next != NULL)
                tmp = tmp->next;
            tmp->next = new_env;
        }
        i++;
    }
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char	*line;
	t_input	*tok;
	list_env	*env_list;

	if (ac != 1)
		return (printf("Error: Too many arguments\n"), 1);
	while(1)
	{
		line = readline("minishell$ ");

		if (!line)
			return(printf("Exiting...\n"), 0);
		if (strlen(line) > 0)
		{
			add_history(line);

			tokenization(line, &tok);
			ft_list_env(env, &env_list);
			expand_variables(&tok, env_list);

			while (tok)
			{
				printf("Token: %s\n", tok->value);
				printf("Type: %d\n", tok->type);
				tok = tok->next;
			}

			pid_t pid = fork();
            if (pid == 0)
                exit(1);
            else
				wait(&pid);
		}
	}
}
