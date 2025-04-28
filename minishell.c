/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:56:34 by obarais           #+#    #+#             */
/*   Updated: 2025/04/28 07:55:44 by obarais          ###   ########.fr       */
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
        if (*env_list == NULL)
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

char **put_the_args(t_input *tok, char *cmd)
{
    char **args;
    int i = 0;
    int j = 0;
    t_input *tmp2;
    t_input *tmp;

    tmp = tok;
    while (strcmp(tmp->value, cmd) != 0)
        tmp = tmp->next;
    tmp = tmp->next;
    tmp2 = tmp;
    while(tmp2 && tmp2->type != PIPE)
    {
        i++;
        tmp2 = tmp2->next;
    }
    args = (char **)malloc(sizeof(char *) * (i + 1));
    if (args == NULL)
        return (NULL);
    while (tmp  && tmp->type != PIPE)
    {
        args[j] = ft_strdup(tmp->value);
        j++;
        tmp = tmp->next;
    }
    args[j] = NULL;
    return (args);
}

int what_direction(char *str)
{
    if (strcmp(str, "<") == 0)
        return 0;
    else if (strcmp(str, ">") == 0)
        return 1;
    else if (strcmp(str, ">>") == 0)
        return 2;
    else if (strcmp(str, "<<") == 0)
        return 3;
    return -1;
}

t_redir *check_derctions(char **args)
{
    int i = 0;
    t_redir *redir = NULL;

    while (args[i] != NULL)
    {
        if (strcmp(args[i], "<") == 0 || strcmp(args[i], ">") == 0 || strcmp(args[i], ">>") == 0 || strcmp(args[i], "<<") == 0)
        {
            t_redir *new_redir = (t_redir *)malloc(sizeof(t_redir));
            new_redir->filename = ft_strdup(args[i + 1]);
            new_redir->type = what_direction(args[i]);
            if (redir == NULL)
            {
                redir = new_redir;
                redir->next = NULL;
            }
            else
            {
                t_redir *tmp = redir;
                while (tmp->next != NULL)
                    tmp = tmp->next;
                tmp->next = new_redir;
                new_redir->next = NULL;
            }
        }
        i++;
    }
    return redir;
}

void	list_commands(t_input *tok, t_command **cmd_list)
{
	t_command *new_cmd;
	t_command *tmp;

	while(tok != NULL)
    {
        new_cmd = (t_command *)malloc(sizeof(t_command));
        new_cmd->cmd = ft_strdup((tok)->value);
        new_cmd->args = put_the_args(tok, tok->value);
        new_cmd->inoutfile = check_derctions(new_cmd->args);
        new_cmd->next = NULL;
        if (*cmd_list == NULL)
            *cmd_list = new_cmd;
        else
        {
            tmp = *cmd_list;
            while (tmp->next != NULL)
                tmp = tmp->next;
            tmp->next = new_cmd;
        }
		while (tok && tok->type != PIPE)
			tok = tok->next;
		if (tok)
			tok = tok->next;
    }
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	char	*line;
	t_input	*tok;
	list_env	*env_list;
	t_command	*cmd_list;

	env_list = NULL;
	cmd_list = NULL;
	tok = NULL;
	if (ac != 1)
		return (printf("Error: Too many arguments\n"), 1);
	while(1)
	{
		line = readline("minishell$ ");

		if (!line)
			return(printf("Exiting...\n"), 1);
		if (strlen(line) > 0)
		{
			add_history(line);

			tokenization(line, &tok);
			ft_list_env(env, &env_list);
			expand_variables(&tok, env_list);
			list_commands(tok, &cmd_list);

            while(tok)
            {
                printf("value :%s\ntype;  %u\n", tok->value, tok->type);
                tok=tok->next;
            }
            int j = 1;
            while (cmd_list)
            {
                printf("command %d:\n", j);
                printf("cmd :%s\n", cmd_list->cmd);
                printf("args :");
                for (size_t i = 0; cmd_list->args[i]; i++)
                {
                    printf("%s  ", cmd_list->args[i]);
                }
                printf("\n");
                while(cmd_list->inoutfile)
                {
                    printf("filename :%s   type:%d\n",  cmd_list->inoutfile->filename, cmd_list->inoutfile->type);
                    cmd_list->inoutfile = cmd_list->inoutfile->next;
                }
                cmd_list = cmd_list->next;
                j++;
            }

            cmd_list = NULL;
			pid_t pid = fork();
            if (pid == 0)
                exit(1);
            else
				wait(&pid);
		}
	}
}
