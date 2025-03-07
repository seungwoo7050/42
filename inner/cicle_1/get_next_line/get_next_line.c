/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:59:52 by seungwok          #+#    #+#             */
/*   Updated: 2023/07/18 18:18:22 by seungwok         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_arr(char **arr_line)
{
	free(*arr_line);
	*arr_line = 0;
	return (0);
}

char	*setline(char *arr_line)
{
	char	*line;
	int		start;

	if (!ft_strchr(arr_line, '\n'))
		return (free_arr(&arr_line));
	start = ft_strchr(arr_line, '\n') - (arr_line) + 1;
	if (arr_line[start] == 0)
		return (free_arr(&arr_line));
	line = ft_substr(arr_line, start, ft_strlen(arr_line) - start);
	free_arr(&arr_line);
	if (line == 0)
		return (0);
	return (line);
}

char	*makeline(char *arr_line)
{
	char	*line;
	int		len;

	if (!ft_strchr(arr_line, '\n'))
		len = ft_strlen(arr_line);
	else
		len = ft_strchr(arr_line, '\n') - (arr_line) + 1;
	line = ft_substr(arr_line, 0, len);
	if (line == 0)
		return (0);
	return (line);
}

char	*readline(char *arr_line, int fd)
{
	int		readsize;
	char	buf[BUFFER_SIZE + 1];

	readsize = 1;
	buf[0] = 0;
	while (readsize > 0 && !ft_strchr(buf, '\n'))
	{
		readsize = read(fd, buf, BUFFER_SIZE);
		if (readsize > 0)
		{
			buf[readsize] = 0;
			arr_line = ft_strjoin(arr_line, buf);
			if (arr_line == 0)
				return (0);
		}
	}
	if (readsize == -1)
		return (free_arr(&arr_line));
	return (arr_line);
}

char	*get_next_line(int fd)
{
	static char	*arr_line[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (0);
	if ((arr_line[fd] && !ft_strchr(arr_line[fd], '\n')) || !arr_line[fd])
		arr_line[fd] = readline(arr_line[fd], fd);
	if (arr_line[fd] == 0)
		return (0);
	line = makeline(arr_line[fd]);
	if (line == 0)
		return (free_arr(&arr_line[fd]));
	arr_line[fd] = setline(arr_line[fd]);
	return (line);
}
