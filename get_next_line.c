/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neda-sil <neda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 04:02:06 by neda-sil          #+#    #+#             */
/*   Updated: 2025/11/30 12:27:27 by neda-sil         ###   ########.fr       */
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
	read_and_stash(fd, stash);
	if (!stash)
		return (NULL);
	extract_line(stash, line);
	clean_up_stash(stash);
	if (!line[0])
	{
		free(stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

void	read_and_stash(int fd, char *stash)
{
	char	*buf;
	ssize_t		readed;

	readed = 1;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return ;
	while (!found_newline(stash) && readed != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return ;
		readed = read(fd, buf, BUFFER_SIZE);
		if ((stash == NULL && readed == 0) || readed == -1)
		{
			free(buf);
			return ;
		}
		buf[readed] = '\0';
		add_stash(stash, buf, readed);
		free(buf);
	}
}

void	add_stash(char	*stash, char *buf, ssize_t readed)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * (len(stash) + 1));
	if (!tmp)
		return ;
	tmp = ft_strdup(stash);
	free(stash);
	stash = malloc(sizeof(char) * (len(tmp) + readed + 1));
	if (!stash)
	{
		free(tmp);
		return ;
	}
	ft_strlcpy(stash, tmp, len(tmp));
	ft_strlcat(stash, buf, readed);
	free(tmp);
}

void	extract_line(char *stash, char *line)
{
	size_t	len_of_line;

	if (!stash)
		return ;
	len_of_line = 0;
	while (stash[len_of_line] && stash[len_of_line] != '\n')
		len_of_line++;
	line = malloc(sizeof(char) * (len_of_line + 1));
	if (!line)
		return ;
	ft_strlcpy(line, stash, len_of_line);
}

void	clean_up_stash(char *stash)
{
	char	*tmp;
	int		len_of_line;
	// int		rest;

	if (!stash)
		return ;
	tmp = ft_strdup(stash);
	len_of_line = 0;
	while (tmp[len_of_line] && tmp[len_of_line] != '\n')
		len_of_line++;
	// rest = 0;
	// while (tmp[len_of_line + rest])
	// 	rest++;
	free(stash);
	stash = ft_strdup(&tmp[len_of_line]);
	free(tmp);
}

#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int	fd;
	char	*line;

	fd = open("./test.txt", O_RDONLY);
	// while (1)
	// {
		line = get_next_line(fd);
		if (!line)
			return (0);
		printf("%s", line);
		free(line);
	// }
	// free(line);
	return (0);
}
