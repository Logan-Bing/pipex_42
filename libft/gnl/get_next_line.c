/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llugez <llugez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:09:40 by llugez            #+#    #+#             */
/*   Updated: 2026/01/25 13:32:23 by llugez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd, char *buffer, char **stash)
{
	int		n;
	char	*new_stash;

	n = 1;
	while (n > 0)
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n < 0)
			return (NULL);
		buffer[n] = '\0';
		if (!*stash)
			*stash = ft_strdup(buffer);
		else
		{
			new_stash = ft_strjoin(*stash, buffer);
			free(*stash);
			*stash = new_stash;
		}
		if (ft_strchr(*stash, '\n'))
			return (set_line(stash));
	}
	return (clean_stash(stash));
}

char	*clean_stash(char **stash)
{
	char	*temp;

	if (!*(*stash))
	{
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
	temp = ft_strdup(*stash);
	free(*stash);
	*stash = NULL;
	return (temp);
}

char	*set_line(char **stash)
{
	char	*line;
	int		len;
	char	*temp;
	char	*ptr_n;

	ptr_n = ft_strchr(*stash, '\n');
	if (!ptr_n)
		return (NULL);
	len = ptr_n - *stash + 1;
	line = ft_substr(*stash, 0, len);
	if (!line)
		return (NULL);
	temp = ft_strdup(ptr_n + 1);
	free(*stash);
	*stash = temp;
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		stash = NULL;
		return (NULL);
	}
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = read_file(fd, buffer, &stash);
	clean_stash(&stash);
	free(buffer);
	return (line);
}

// int main ()
// {
// 	int fd = open("file.txt", O_RDONLY);
// 	char *res;
// 	while ((res = get_next_line(fd)) != NULL) {
// 		printf("%s", res);
// 		free(res);
// 	}
// 	printf("\n");
// 	// Check for NULL at the end;
// 	printf("%s", res);
// 	// // STANDART OUTPUT
// 	// char *line;
// 	// while ((line = get_next_line(0)) != NULL) {
// 	// 	printf("%s", line);
// 	// 	free(line);
// 	// }
// 	// printf("%s", line);
// }
