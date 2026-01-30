/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llugez <llugez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:07:11 by llugez            #+#    #+#             */
/*   Updated: 2026/01/30 11:40:09 by llugez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/header.h"

void	clean_2d_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	clean_list(t_cmd_constructor *list)
{
	t_cmd_constructor	*current_node;
	t_cmd_constructor	*temp;

	current_node = list;
	while (current_node->prev)
		current_node = current_node->prev;
	while (current_node)
	{
		temp = current_node->next;
		clean_2d_tab(current_node->cmd);
		free(current_node);
		current_node = temp;
	}
	list = NULL;
}

void	clean_data(t_data *data)
{
	if (data->tube)
		free(data->tube);
	if (data->pids)
		free(data->pids);
	if (data->list_cmd)
		clean_2d_tab(data->list_cmd);
	if (data->shell)
		free(data->shell);
}

void	clean_all(t_cmd_constructor *list, t_data *data)
{
	clean_data(data);
	clean_list(list);
}
