/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstart.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llugez <llugez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:09:16 by llugez            #+#    #+#             */
/*   Updated: 2026/01/25 16:12:22 by llugez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstart(char *big, char *little)
{
	int	i;

	i = 0;
	while (big[i] == little[i] && big[i])
	{
		i++;
		if (little[i] == '\0')
			return (big);
	}
	return (NULL);
}
