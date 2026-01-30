/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llugez <llugez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:15:17 by llugez            #+#    #+#             */
/*   Updated: 2025/12/28 18:07:49 by llugez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// • %c Prints a single character.
int	ft_putchar(char c)
{
	return (write(2, &c, 1));
}

// • %s Prints a string (as defined by the common C convention).
int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_putstr("(null)"));
	while (str[i])
		i++;
	write(2, str, i);
	return (i);
}
