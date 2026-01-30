/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llugez <llugez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:06:00 by llugez            #+#    #+#             */
/*   Updated: 2026/01/14 13:06:47 by llugez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/header.h"

t_cmd_constructor	*create_node(char *full_cmd)
{
	t_cmd_constructor	*new_node;
	char				**splited_cmd;

	splited_cmd = ft_split(full_cmd, ' ');
	if (!splited_cmd)
		return (NULL);
	new_node = malloc(sizeof(t_cmd_constructor));
	if (!new_node)
		return (NULL);
	new_node->cmd = splited_cmd;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	push_back(t_cmd_constructor **head, char *full_cmd)
{
	t_cmd_constructor	*new_node;
	t_cmd_constructor	*current_node;

	new_node = create_node(full_cmd);
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	current_node = *head;
	while (current_node->next != NULL)
		current_node = current_node->next;
	current_node->next = new_node;
	new_node->prev = current_node;
}

void	init_list(t_cmd_constructor **head, char **list_cmd, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		push_back(head, list_cmd[i]);
		i++;
	}
}
