/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_get_next_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:06:01 by ttakino           #+#    #+#             */
/*   Updated: 2024/05/14 17:52:15 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 4
#endif

char	*my_return_line(char *save, t_list *str)
{
	char	*line;
	size_t	len;

	if (str == NULL)
	{
		len = ft_strlen(save);
		line = (char *)malloc(len + 1);
		if (line == NULL)
			return (NULL);
		ft_memcpy(line, save, len + 1);
		line[len] = '\0';
		return (line);
	}
	else
	{
		line = "";
		while (str->next != NULL)
		{
			if (ft_strlen(line) != 0)
				free(line);
			line = ft_strjoin(line, str->content);
			str = str->next;
		}
		return (line);
	}
}

char	*new_get_next_line(int fd)
{
	static char		buf[BUFFER_SIZE];
	static int		bytes;
	t_list			node;
	static t_list	*str;
	static int		i = 0;
	int				save_i;
	char			save[BUFFER_SIZE];

	//ファイルの終端に達するまでループ
	while (1)
	{
		printf("i = %d\n", i);
		//読み込む
		if (i == 0)
			bytes = read(fd, buf, BUFFER_SIZE);
		printf("buf = %s\n", buf);
		if (bytes <= 0)
		{
			printf("終端\n");
			return (NULL);
		}
		// printf("bytes = %d\n", BUFFER_SIZE);
		//bufの改行チェック
		save_i = 0;
		while (i < BUFFER_SIZE)
		{
			printf("i = %d\n", i);
			if (buf[i] == '\n')
			{
				//改行が入っていた場合はreturn
				save[save_i] = buf[i];
				save[save_i + 1] = '\0';
				while (buf[i] == '\n')
					i++;
				printf("save = %s\n", save);
				return (my_return_line(save, str));
			}
			else if (buf[i] == '\0')
			{
				save[save_i] = buf[i];
				i = 0;
				str = NULL;
				return (my_return_line(save, str));
			}
			else
				save[save_i] = buf[i];
			i++;
			save_i++;
		}
		//bufに改行が入っていなかった場合 = リストにsaveを追加
		str = (t_list *)malloc(sizeof(t_list));
		if (str == NULL)
			return (NULL);
		printf("save = %s\n", save);
		node.content = save;
		node.next = NULL;
		//i = 0
		i = 0;
		ft_lstadd_back(&str, &node);
		printf("o\n");
	}
	return (my_return_line(save, str));
	// return (NULL);
}

#include <fcntl.h>

int	main(int argc, char **argv)
{
	char	*file;
	int		fd;
	char	*line;
	int		cnt;

	if (argc != 2)
	{
		printf("指定できるファイルは一個です。\n");
		return (1);
	}
	file = argv[1];
	fd = open(file, O_RDONLY);
	cnt = 0;
	while (1)
	{
		// printf("cnt : %d\n", cnt);
		line = new_get_next_line(fd);
		if (line == NULL)
		{
			// printf("ファイルの読み込みに失敗しました。\n");
			return (0);
		}
		printf("line = %s", line);
		cnt++;
	}
	return (0);
}
