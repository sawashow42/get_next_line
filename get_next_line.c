/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shsawaki <shsawaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:39:52 by shsawaki          #+#    #+#             */
/*   Updated: 2022/09/02 00:59:57 by shsawaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

char	*ft_read(int fd, char *save)//saveに改行がくるまでreadし、saveに結合する関数
{
	int		cc;
	char	*buf;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	cc = 1;
	while (!ft_strchr(save, '\n') && cc != 0)
	{
		cc = read(fd, buf, BUFFER_SIZE);
		if (cc <= 0)
		{
			free(buf);
			return (NULL);
		}
		buf[cc] = '\0';
		// printf("%d\n", __LINE__);
		//printf("%s\n",buf);
		save = ft_strjoin(save, buf);
		//printf("%s\n", save);
		// printf("%d\n", __LINE__);
	}
	free(buf);
	return (save);
}

char	*putstr_proce(char *save)//出力する文字列の処理、改行より前までを入れる
{
	int		i;
	char	*put_str;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	put_str = malloc(sizeof(char) * (i + 2));
	if (!put_str)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		put_str[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
		put_str[i++] = '\n';
	put_str[i] = '\0';
	return (put_str);
}

char	*save_proce(char *save)//saveにおける改行以降を更新する処理
{
	char	*new_save;
	int		i;
	int		j;
	
	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	new_save = malloc(sizeof(char) * (ft_strlen(save) - i + 1));
	if (!new_save)
		return (NULL);
	i++;
	j = 0;
	while (save[i])
		new_save[j++] = save[i++];
	new_save[j] = '\0';
	free(save);
	return (new_save);
}

char *get_next_line(int fd)
{
	static char	*save;
	char		*put_str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = ft_read(fd, save);
	// if (!save)
	// 	return (NULL);
	put_str = putstr_proce(save);
	if (!put_str)
		return (NULL);
	//printf("%s\n", put_str);
	save = save_proce(save);
	// if (!save)
	// 	return (NULL);
	//printf("%s\n", save);
	return (put_str);
}

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