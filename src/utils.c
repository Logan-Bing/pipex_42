/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llugez <llugez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:05:19 by llugez            #+#    #+#             */
/*   Updated: 2026/01/14 13:11:00 by llugez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/header.h"

// Ajoute un slash avant la commande
// exemple "cat" -> "/cat"
char	*prepend_slash(const char *cmd)
{
	char	*slash_cmd;
	int		len;

	len = ft_strlen(cmd);
	slash_cmd = malloc(len + 2);
	if (!slash_cmd)
		return (NULL);
	slash_cmd[0] = '/';
	ft_strlcpy(slash_cmd + 1, cmd, len + 1);
	return (slash_cmd);
}

// Fonction utilitaire pour lister les commandes passer dans argv
char	**build_list_cmd(int nb_cmd, char *argv[], int start)
{
	char	**list_cmd;
	int		i;

	i = 0;
	list_cmd = malloc(sizeof(char *) * (nb_cmd + 1));
	if (!list_cmd)
		return (NULL);
	while (i < nb_cmd)
	{
		list_cmd[i] = prepend_slash(argv[start + i]);
		i++;
	}
	list_cmd[i] = NULL;
	return (list_cmd);
}
