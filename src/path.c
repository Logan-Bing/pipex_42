/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llugez <llugez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:05:34 by llugez            #+#    #+#             */
/*   Updated: 2026/01/25 15:52:43 by llugez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/header.h"

char	*get_path_env(char *envp[], char *var)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strstart(envp[i], var))
			return (envp[i]);
		i++;
	}
	return (NULL);
}

char	*get_shell_path(char *envp[], t_data *data)
{
	char	**shell_path;
	char	*shell;
	int		i;

	i = 0;
	shell_path = ft_split(get_path_env(envp, SHELL_PATH), '/');
	if (!shell_path)
		handle_error("Impossible get shell path", data);
	while (shell_path[i + 1] != NULL)
		i++;
	shell = ft_strdup(shell_path[i]);
	clean_2d_tab(shell_path);
	return (shell);
}

char	*get_path_cmd(char *envp[], char *cmd)
{
	char	**path_list;
	char	*path_cmd;
	int		i;

	i = 0;
	if (access(cmd, F_OK | X_OK) == 0)
	{
		path_cmd = cmd;
		return (path_cmd);
	}
	path_list = ft_split(get_path_env(envp, ENV_PATH), ':');
	while (path_list[i])
	{
		path_cmd = ft_strjoin(path_list[i], cmd);
		if (access(path_cmd, F_OK | X_OK) == 0)
			return (path_cmd);
		else
			free(path_cmd);
		i++;
	}
	clean_2d_tab(path_list);
	return (NULL);
}
