/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shsawaki <shsawaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:39:52 by shsawaki          #+#    #+#             */
/*   Updated: 2022/09/01 00:25:52 by shsawaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*save_proce(char *save, int save_tmp)
{
	char	*new_save;
	int		i;
	int		j;

	new_save = malloc(sizeof(char) * (ft_strlen(save) - save_tmp));
	if (!new_save)
		return (NULL);
	i = ++save_tmp;
	j = 0;
	while(save[i])
		new_save[j++] = save[i++];
	new_save[j] = '\0';
	return (new_save);
}

char *get_next_line(int fd)
{
	char		*buf;
	static char	*save;
	char		*put_str;
	int			cc;
	int			i;
	int			j;

	if (fd < 0)
		return (NULL);
	*save = 0;
	while (ft_strchr(save, '\n') == NULL)
	{
		cc = read(fd, buf, BUFFER_SIZE);
		if (cc < 0)
			return (NULL);
		save = ft_strjoin(save, buf);
	}
	i = 0;
	while (save[i] != '\n')
		i++;
	put_str = malloc(sizeof(char) * (i + 2));
	if (!put_str)
		return (NULL);
	i = 0;
	j = 0;
	while (save[i] != '\n')
		put_str[j++] = save[i++];
	put_str[j++] = '\n';
	put_str[j] = '\0';
	save = save_proce(save, i);
	return (put_str);
}

#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*line;

	line = "";
	fd = open("test.txt", O_RDONLY);
	while (line)
	{
		line = get_next_line(fd);
		printf("> %s", line);
		free(line);
	}
	return (0);
}