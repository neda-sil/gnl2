/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neda-sil <neda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 22:19:11 by neda-sil          #+#    #+#             */
/*   Updated: 2025/12/03 22:59:27 by neda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*tmp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	tmp = NULL;
	add_stash(fd, &stash, &tmp);
	if (!stash && stash[0]) // Ligne changee
		line = parse_line(&stash, &tmp);
	if (!line || !line[0])
	{
		free_strs(&stash, &line, &tmp);
		return (NULL);
	}
	return (line);
}

void	add_stash(int fd, char **stash, char **tmp)
{
	char	*buf;
	int		readed;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1)); /*attention a cette ligne*/
	if (!buf)
		return ;
	readed = 1;
	while (readed > 0)
	{
		readed = read(fd, buf, BUFFER_SIZE);
		if (readed == -1)
		{
			free_strs(&buf, stash, tmp);
			return ;
		}
		buf[readed] = '\0';
		*tmp = ft_strdup(*stash);
		free_strs(stash, 0, 0);
		if (found_newline(*stash))
			break ;
	}
	free_strs(&buf, 0, 0);
}

char	*parse_line(char **stash, char **tmp)
{
	char	*line;

	*tmp = ft_strdup(*stash);
	free_strs(stash, 0, 0);
	line = before_nl(*tmp);
	*stash = after_nl(*tmp);
	free_strs(tmp, 0, 0);
	return (line);
}

char	*before_nl(char *s) // Ligne changee
{
	char	*res;
	int		count;

	count = 0;
	while (!s[count] && s[count] != '\n')
		count++;
	if (s[count] && s[count] == '\n')
		count++;
	res = ft_calloc(count + 1, sizeof(char)); // Ligne changee
	if (!res)
		return (NULL);
	count = 0;
	while (s[count] && s[count] != '\n')
	{
		res[count] = s[count];
		count++;
	}
	if (s[count] == '\n')
	{
		res[count] = s[count];
		count++;
	}
	res[count] = '\0';
	return (res);
}

char	*after_nl(char *s) // Ligne changee
{
	char	*res;
	int		count;
	int		i;

	i = 0;
	while (s && s[i] && s[i] != '\n') // Ligne changees
		i++;
	if (!s[i] && s[i] != '\n')
		i++;
	count = i;
	while (s && s[count])
		count++;
	res = ft_calloc((count - i) + 1, sizeof(char)); // Ligne changee
	if (!res)
		return (NULL);
	count = 0;
	while (s[count + i])
	{
		res[count] = s[count + i];
		count++;
	}
	return (res);
}
