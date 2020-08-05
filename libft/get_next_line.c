/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 21:22:55 by jnannie           #+#    #+#             */
/*   Updated: 2020/08/05 20:07:31 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define FDLIMIT 4096
#define ABOVE_ZERO 1
#define THEREISNEWLINE 1
#define ERROROCCURRED -1
#define BUFFER_SIZE 1024

static size_t		line_length(const char *str)
{
	size_t			i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	return (i);
}

static int			read_line_from_buf(char **line, char *buf)
{
	size_t			ll;
	char			*sub;
	char			*temp_line;

	ll = line_length(buf);
	sub = ft_substr(buf, 0, ll);
	temp_line = *line;
	*line = ft_strjoin(temp_line, sub);
	free(temp_line);
	free(sub);
	if (!(*line))
		return (-1);
	if (*(buf + ll) == '\n')
	{
		ft_memmove(buf, buf + ll + 1, BUFFER_SIZE - ll - 1);
		ft_bzero(buf + BUFFER_SIZE - ll - 1, ll + 1);
		return (1);
	}
	return (0);
}

static int			free_memory(char **buf_tab, int fd, char **line, int err)
{
	free(buf_tab[fd]);
	buf_tab[fd] = 0;
	if (err == -1 && line)
	{
		free(*line);
		*line = 0;
	}
	return (err);
}

int					get_next_line(int fd, char **line)
{
	static char		*buf_tab[FDLIMIT];
	int				r;

	if (fd >= FDLIMIT || fd < 0 || BUFFER_SIZE < 1)
		return (-1);
	if (!line || !(*line = ft_strdup("")))
		return (free_memory(buf_tab, fd, line, -1));
	r = ABOVE_ZERO;
	if (!buf_tab[fd])
		if ((!(buf_tab[fd] = ft_calloc(BUFFER_SIZE + 1, sizeof(char))) ||
			(r = read(fd, buf_tab[fd], BUFFER_SIZE)) == -1))
			return (free_memory(buf_tab, fd, line, -1));
	while (r > 0)
	{
		if ((r = read_line_from_buf(line, buf_tab[fd])) == THEREISNEWLINE)
			return (1);
		else if (r == ERROROCCURRED)
			break ;
		ft_bzero(buf_tab[fd], BUFFER_SIZE);
		r = read(fd, buf_tab[fd], BUFFER_SIZE);
	}
	return (free_memory(buf_tab, fd, line, r));
}
