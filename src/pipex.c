/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llugez <llugez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:05:37 by llugez            #+#    #+#             */
/*   Updated: 2026/01/30 13:20:28 by llugez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/header.h"

void	execute_command(t_cmd_constructor *act_cmd, t_data *data)
{
	act_cmd->path_cmd = get_path_cmd(data->envp, act_cmd->cmd[0]);
	if (!act_cmd->path_cmd)
		handle_execve_error(data, act_cmd);
	if (execve(act_cmd->path_cmd, act_cmd->cmd, data->envp) < 9)
	{
		clean_all(act_cmd, data);
		exit(1);
	}
}

void	close_parent_fd(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_tube)
	{
		close(data->tube[i][0]);
		close(data->tube[i][1]);
		i++;
	}
}

void	close_fds(t_data *data, int i)
{
	int	j;

	j = 0;
	while (j < data->nb_tube)
	{
		if (j != i - 1)
			close(data->tube[j][0]);
		if (j != i)
			close(data->tube[j][1]);
		j++;
	}
}

void	wait_for_child_pr(t_data *data, t_cmd_constructor *act_cmd)
{
	int	i;
	int	status;

	i = 0;
	close_parent_fd(data);
	while (i < data->nb_cmd)
	{
		waitpid(data->pids[i], &status, 0);
		if (i == data->nb_cmd - 1)
		{
			clean_all(act_cmd, data);
			if (!data->get_outfile_perm)
				exit(EXIT_CODE_PERMISSION);
			exit(WEXITSTATUS(status));
		}
		i++;
	}
}

void	pipex(t_data *data, t_cmd_constructor *act_cmd)
{
	int					i;
	t_cmd_constructor	*head;

	i = 0;
	head = act_cmd;
	while (i < data->nb_cmd)
	{
		data->pids[i] = fork();
		if (data->pids[i] < 0)
			handle_error("fork", data);
		if (data->pids[i] == 0)
		{
			close_fds(data, i);
			if (i == 0)
				dup_first_command(i, data);
			else if (i != data->nb_cmd - 1)
				dup_inter_command(i, data);
			else
				dup_last_command(i, data);
			execute_command(act_cmd, data);
		}
		act_cmd = act_cmd->next;
		i++;
	}
	wait_for_child_pr(data, head);
}
