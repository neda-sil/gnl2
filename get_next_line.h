/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neda-sil <neda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:54:40 by neda-sil          #+#    #+#             */
/*   Updated: 2025/12/07 21:25:32 by neda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
void	add_stash(int fd, char **stash, char **tmp);
int		found_nl(const char *s);
void	free_strs(char **str1, char **str2, char **str3);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_strjoin_gnl(const char *s1, const char *s2);
char	*parse_line(char **stash, char **tmp);
char	*before_nl(const char *s);
char	*after_nl(const char *s);

#endif