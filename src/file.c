/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llugez <llugez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:05:50 by llugez            #+#    #+#             */
/*   Updated: 2026/01/25 15:43:09 by llugez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/header.h"

// Verification des droits + redirection STDIN et STDOUT
int	handle_infile(t_data *data, char *infile_path)
{
	int	fd;

	fd = open(infile_path, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("%s: %s: %s\n", data->shell, strerror(errno), data->infile);
		fd = open("/dev/null", O_RDONLY);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		handle_error("dup2", data);
	return (fd);
}

int	handle_tempfile(t_data *data)
{
	int	fd;

	fd = open("tmp.txt", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
	{
		perror("open temp");
		clean_data(data);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	handle_outfile(t_data *data, char *outfile_path)
{
	int	fd;

	fd = open(outfile_path, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
	{
		ft_printf("%s: %s: %s\n", data->shell, strerror(errno), data->outfile);
		fd = open("/dev/null", O_WRONLY);
		data->get_outfile_perm = 0;
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
		handle_error("dup2", data);
	return (fd);
}
