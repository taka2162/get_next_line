/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:34:07 by ttakino           #+#    #+#             */
/*   Updated: 2024/05/14 15:28:01 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 256
#endif

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE];
	static int	bytesRead = 0;
	static int	totalRead = 0;
	int			i;
	static char	save[BUFFER_SIZE];
	char		*result;

	// bytesRead = 0;
	result = NULL;
	printf("totalRead = %d\n", totalRead);
	printf("save = %s\n", save);
	while (1)
	{
		if (totalRead == 0)
			bytesRead = read(fd, buf, BUFFER_SIZE);
		else
		{
			ft_memcpy(buf, save, ft_strlen(save));
		}
		if (bytesRead <= 0)
		{
			printf("bytesRead <= 0: bytesRead = %d\n", bytesRead);
			printf("ファイルの終端に到達\n");
			break ;
		}
		i = 0;
		printf("bytesRead = %d\n", bytesRead);
		while (i < bytesRead)
		{
			if (BUFFER_SIZE < totalRead + i + 1)
			{
				free(result);
				return (NULL);
			}
			if (buf[i] == '\n')
			{
				printf("改行見つかった\n");
				printf("buf = %s\n", buf);
				printf("i = %d\n", i);
				result = (char *)malloc(totalRead + i + 2);
				if (result == NULL)
					return (NULL);
				result[i + 1] = '\0';
				// ft_memcpy(result, save, totalRead);
				ft_memcpy(result, buf, i + 1);
				ft_memcpy(save, buf + i + 1, bytesRead - i - 1);
				totalRead += i + 1;
				return (result);
			}
			i++;
			// if (buf[i] == '\0')
			// 	break ;
		}
		printf("改行見つからなかった\n");
		ft_memcpy(save + totalRead, buf, bytesRead);
		totalRead += bytesRead;
	}
	if (0 < totalRead)
	{
		printf("totalRead > 0: totalRead = %d\n", totalRead);
		result = (char *)malloc(totalRead + 1);
		if (result == NULL)
			return (NULL);
		ft_memcpy(result, save, totalRead);
		totalRead = 0;
		return (result);
	}
	return (NULL);
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
		printf("cnt : %d\n", cnt);
		line = get_next_line(fd);
		if (line == NULL)
		{
			printf("ファイルの読み込みに失敗しました。\n");
			return (0);
		}
		printf("line = %s", line);
		cnt++;
	}
	return (0);
}
