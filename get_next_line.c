/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neda-sil <neda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:54:09 by neda-sil          #+#    #+#             */
/*   Updated: 2025/12/02 21:10:10 by neda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, &line, 0) < 0)
		return (NULL);
	line = NULL;
	stash = add_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = clean_stash(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		free(line);
		line = NULL;
		return (NULL);
	}
	return (line);
}

char	*add_stash(int fd, char *stash)
{
	char		*buf;
	ssize_t		size;

	size = 1;
	while (!found_newline(stash) && size > 0)
	{
		buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!buf)
			return (NULL);
		size = read(fd, &buf, BUFFER_SIZE);
		if (size < 0)
		{
			free(buf);
			return (stash);
		}
		stash = ft_strjoin(buf, stash);
		free(buf);
	}
	return (stash);
}

char	*extract_line(char *stash)
{
	int		i;
	int		newline;
	char	*line;

	if (!stash)
		return (NULL);
	newline = 0;
	while (stash[newline] && stash[newline] != '\n')
		newline++;
	line = malloc(sizeof(char) * (newline + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i <= newline)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*clean_stash(char *stash)
{
	char	*new;
	int		i;
	int		newline;

	newline = 0;
	while (stash[newline] && stash[newline] != '\n')
		newline++;
	if (!stash[newline])
	{
		free(stash);
		return (NULL);
	}
	new = malloc(sizeof(char) * (ft_strlen(stash) - newline + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (stash[newline + i])
	{
		new[i] = stash[newline + i];
		i++;
	}
	free (stash);
	return (new);
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int	fd;
// 	char	*line;

// 	fd = open("./test.txt", O_RDONLY);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			return (0);
// 		printf("%s", line);
// 		free(line);
// 	}
// 	free(line);
// 	return (0);
// }
