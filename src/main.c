/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llugez <llugez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:05:28 by llugez            #+#    #+#             */
/*   Updated: 2026/01/30 13:26:15 by llugez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/header.h"

// pas oublier de free data.list_cmd avec clean2dtab
// pas oublier de free data.tube
// pas oublier de free t_cmd_constructor

void	pipe_tube(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmd)
	{
		if (pipe(data->tube[i]) < 0)
			handle_error("pipe", data);
		i++;
	}
}

void	init_data(t_data *data, char *argv[], int argc)
{
	data->infile = argv[1];
	data->nb_cmd = argc - 3;
	data->fd_inf = handle_infile(data, argv[1]);
	data->nb_tube = data->nb_cmd - 1;
	data->list_cmd = build_list_cmd(data->nb_cmd, argv, 2);
	data->tube = malloc(data->nb_cmd * sizeof(int [2]));
	data->fd_out = handle_outfile(data, data->outfile);
	if (!data->tube)
		handle_error("Malloc data->tube", data);
	pipe_tube(data);
	data->pids = malloc(sizeof(pid_t) * data->nb_cmd);
	if (!data->pids)
		handle_error("Malloc data->pids", data);
}

void	init(t_data *data, char *argv[], int argc, char *envp[])
{
	if (argc < 5)
	{
		ft_printf("Expected 4 arguments minimun");
		exit(EXIT_FAILURE);
	}
	data->pids = NULL;
	data->tube = NULL;
	data->list_cmd = NULL;
	data->outfile = argv[argc - 1];
	data->envp = envp;
	data->shell = get_shell_path(envp, data);
	data->get_outfile_perm = 1;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data				data;
	t_cmd_constructor	*act_cmd;

	act_cmd = NULL;
	init(&data, argv, argc, envp);
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		handle_heredoc(&act_cmd, &data, argv, argc);
	}
	else
	{
		init_data(&data, argv, argc);
		init_list(&act_cmd, data.list_cmd, data.nb_cmd);
		pipex(&data, act_cmd);
		close(data.fd_inf);
	}
	close(data.fd_out);
}
