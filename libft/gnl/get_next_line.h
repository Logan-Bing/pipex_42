/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llugez <llugez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:10:28 by llugez            #+#    #+#             */
/*   Updated: 2026/01/02 17:58:51 by llugez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft.h"

char	*get_next_line(int fd);
char	*set_line(char **stash);
char	*read_file(int fd, char *buffer, char **stash);
char	*clean_stash(char **stash);

// char	*ft_strchr(char *str, int c);
// char	*ft_strdup(char *str);
// char	*ft_substr(const char *s, unsigned int start, size_t len);
// char	*ft_strjoin(char *s1, char *s2);
// int		ft_strlen(const char *str);

#endif