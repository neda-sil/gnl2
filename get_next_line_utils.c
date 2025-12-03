/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neda-sil <neda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:54:11 by neda-sil          #+#    #+#             */
/*   Updated: 2025/12/03 22:59:58 by neda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_newline(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	free_strs(char **str1, char **str2, char **str3)
{
	if (str1 && *str1)
	{
		free(str1);
		*str1 = NULL;
	}
	if (str2 && *str2)
	{
		free(*str2);
		*str2 = NULL;
	}
	if (str3 && *str3)
	{
		free(*str3);
		*str3 = NULL;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*r;
	unsigned char	*p;
	size_t			total;

	total = nmemb * size;
	r = malloc(total);
	if (!r)
		return (NULL);
	p = (unsigned char *)r;
	while (total != 0)
	{
		*p = '\0';
		p++;
		total--;
	}
	return (r);
}

char	*ft_strdup(char *s1)
{
	char	*s2;
	int		i;

	if (!s1)
		return (NULL); // Ligne changee
	i = 0;
	while (s1[i])
		i++;
	s2 = ft_malloc(i + 1, sizeof(char)); // Ligne changee
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	return (s2);
}
