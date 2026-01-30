/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llugez <llugez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:05:53 by llugez            #+#    #+#             */
/*   Updated: 2026/01/25 15:30:00 by llugez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/header.h"

void	init_heredoc_data(t_data *data, int argc, char *argv[])
{
	data->nb_cmd = argc - 4;
	data->nb_tube = data->nb_cmd - 1;
	data->limiter = ft_strjoin(argv[2], "\n");
	data->fd_tmp = handle_tempfile(data);
	data->list_cmd = build_list_cmd(data->nb_cmd, argv, 3);
	data->tube = malloc(data->nb_cmd * sizeof(int [2]));
	if (!data->tube)
		handle_error("Malloc data->tube", data);
	pipe_tube(data);
	data->pids = malloc(sizeof(pid_t) * data->nb_cmd);
	if (!data->pids)
		handle_error("Malloc data->pids", data);
}

void	check_for_limiter(t_data *data)
{
	char	*line;

	while (1)
	{
		ft_printf("pipe heredoc> ");
		line = get_next_line(STDIN_FILENO);
		if (ft_strcmp(line, data->limiter) == 0)
		{
			free(line);
			free(data->limiter);
			break ;
		}
		write(data->fd_tmp, line, ft_strlen(line));
		free(line);
	}
	close(data->fd_tmp);
}

void	handle_heredoc(t_cmd_constructor **act_cmd,
	t_data *data,
	char *argv[],
	int argc)
{
	init_heredoc_data(data, argc, argv);
	init_list(act_cmd, data->list_cmd, data->nb_cmd);
	check_for_limiter(data);
	data->fd_tmp = open("tmp.txt", O_RDONLY);
	if (data->fd_tmp < 0)
		ft_printf("erreur ouverture\n");
	dup2(data->fd_tmp, STDIN_FILENO);
	pipex(data, *act_cmd);
	unlink("tmp.txt");
}
