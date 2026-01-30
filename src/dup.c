/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llugez <llugez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:07:30 by llugez            #+#    #+#             */
/*   Updated: 2026/01/25 15:24:56 by llugez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/header.h"

void	dup_first_command(int i, t_data *data)
{
	if (dup2(data->tube[i][1], STDOUT_FILENO) < 0)
		handle_error("dup2", data);
	close(data->tube[i][1]);
}

void	dup_inter_command(int i, t_data *data)
{
	if (dup2(data->tube[i - 1][0], STDIN_FILENO) < 0)
		handle_error("dup2", data);
	if (dup2(data->tube[i][1], STDOUT_FILENO) < 0)
		handle_error("dup2", data);
	close(data->tube[i - 1][0]);
	close(data->tube[i][1]);
}

void	dup_last_command(int i, t_data *data)
{
	if (dup2(data->tube[i - 1][0], STDIN_FILENO) < 0)
		handle_error("dup2", data);
	close(data->tube[i - 1][0]);
}
