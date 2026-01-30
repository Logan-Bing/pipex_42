/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llugez <llugez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:05:47 by llugez            #+#    #+#             */
/*   Updated: 2026/01/14 13:07:41 by llugez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/header.h"

void	handle_error(const char *message, t_data *data)
{
	perror(message);
	clean_data(data);
	exit(EXIT_FAILURE);
}

void	handle_execve_error(t_data *data, t_cmd_constructor *act_cmd)
{
	ft_printf("command not found: %s\n", act_cmd->cmd[0] + 1);
	clean_list(&act_cmd);
	clean_data(data);
    exit(127);
}
