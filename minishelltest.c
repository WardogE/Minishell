/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishelltest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbullock <vbullock@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 17:24:24 by vbullock          #+#    #+#             */
/*   Updated: 2025/09/29 19:52:24 by vbullock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64

char	*find_in_path(const char *cmd)
{
	char	*fullpath;
	char	*path;
	char	**dir;
	int		i;
	int		count;

	i = 0;
	count = 1;
	path = getenv("PATH");
	if (!path)
		return (NULL);
	while (path[i])
	{
		if (path[i] == ':')
			count++;
		i++;
	}
	dir = ft_split(path, ':');
	i = 0;
	while (dir[i])
	{
		if (ft_strlen(dir[i]) + ft_strlen(cmd) < MAX_INPUT)
		{
			fullpath = ft_strjoin(ft_strjoin(dir[i], "/"), cmd);
			if (access(fullpath, X_OK) == 0)
			{
				ft_free(dir, count);
				return (fullpath);
			}
			free(fullpath);
		}
		i++;
	}
	ft_free(dir, count);
	return (NULL);
}

void	printprompt(void)
{
		printf("\n░  ░░░░  ░░  ░░░░  ░░░      ░░░  ░░░░  ░░        ░░  ░░░░░░░░  ░░░░░░░\n");
		printf("▒   ▒▒   ▒▒▒  ▒▒  ▒▒▒  ▒▒▒▒▒▒▒▒  ▒▒▒▒  ▒▒  ▒▒▒▒▒▒▒▒  ▒▒▒▒▒▒▒▒  ▒▒▒▒▒▒▒\n");
		printf("▓        ▓▓▓▓    ▓▓▓▓▓      ▓▓▓        ▓▓      ▓▓▓▓  ▓▓▓▓▓▓▓▓  ▓▓▓▓▓▓▓\n");
		printf("█  █  █  █████  ███████████  ██  ████  ██  ████████  ████████  ███████\n");
		printf("█  ████  █████  ██████      ███  ████  ██        ██        ██        █\n\n");
		printf("Input prompt> ");
}

int main(void)
{
	extern char	**environ;
	char		input[MAX_INPUT];
	char		*args[MAX_ARGS];
	pid_t		pid;
	int			status;
	int			i;
	char		*token;
	char		*cmd_path;
	char		*found;

	while (1)
	{
		printprompt();
		fflush(stdout);
		if (fgets(input, sizeof(input), stdin) == NULL)
			break ;
		input[strcspn(input, "\n")] = '\0';
		if (strcmp(input, "exit") == 0)
			break ;
		i = 0;
		token = strtok(input, " ");
		while (token != NULL && i < MAX_ARGS - 1)
		{
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;
		if (args[0] == NULL)
		{
			continue ;
		}
		cmd_path = args[0];
		if (strchr(args[0], '/') == NULL)
		{
			found = find_in_path(args[0]);
			if (found)
				cmd_path = found;
		}
		pid = fork();
		if (pid == 0)
		{
			if (execve(cmd_path, args, environ) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
		}
		else
		{
			perror("fork");
		}
	}
	return (0);
}