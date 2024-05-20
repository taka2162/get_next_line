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

char	*generate_new_save(char **save, char **buf, int bytes)
{
	char	*tmp;

	if (*save == NULL)
	{
		tmp = (char *)malloc(bytes + 1);
		if (tmp == NULL)
			return (NULL);
		ft_memcpy(tmp, *buf, bytes + 1);
		free(*buf);
		*buf = NULL;
		*save = tmp;
		return (*save);
	}
	else
	{
		tmp = ft_strjoin(*save, *buf);
		if (tmp == NULL)
			return (free(*buf), free(*save), *buf = NULL, *save = NULL, NULL);
		return (free(*buf), free(*save), *buf = NULL, tmp);
	}
}

char	*generate_line(char **save)
{
	char	*result;
	char	*new_line_pos;
	char	*tmp_change;
	int		save_len;

	if (*save == NULL)
		return (NULL);
	new_line_pos = ft_strchr(*save, '\n');
	*new_line_pos = '\0';
	save_len = ft_strlen(*save);
	result = (char *)malloc(save_len + 2);
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, *save, save_len);
	result[save_len + 1] = '\0';
	result[save_len] = '\n';
	tmp_change = ft_strdup(++new_line_pos);
	if (tmp_change == NULL)
	{
		free(result);
		return (NULL);
	}
	free(*save);
	*save = tmp_change;
	return (result);
}

char	*end_of_loop(char **buf, char **save, int bytes)
{
	char	*tmp;

	if (bytes == -1)
		return (free(*save), free(*buf), *save = NULL, *buf = NULL, NULL);
	if (*save != NULL)
	{
		if (**save == '\0')
		{
			free(*save);
			*save = NULL;
		}
		tmp = *save;
		return (free(*buf), *buf = NULL, *save = NULL, tmp);
	}
	return (free(*buf), free(*save), *buf = NULL, *save = NULL, NULL);
}

char	*return_line(int fd, int bytes)
{
	char		*buf;
	static char	*save = NULL;

	buf = NULL;
	while (1)
	{
		if (ft_strchr(save, '\n') == NULL)
		{
			buf = (char *)malloc(BUFFER_SIZE + 1);
			if (buf == NULL)
				return (NULL);
			bytes = read(fd, buf, BUFFER_SIZE);
			if (bytes <= 0)
				break ;
			buf[bytes] = '\0';
			save = generate_new_save(&save, &buf, bytes);
		}
		if (ft_strchr(save, '\n') != NULL)
			return (generate_line(&save));
	}
	return (end_of_loop(&buf, &save, bytes));
}

char	*get_next_line(int fd)
{
	int		bytes;

	if (BUFFER_SIZE < 0 || INT_MAX < BUFFER_SIZE || fd < 0 || OPEN_MAX < fd)
		return (NULL);
	bytes = 0;
	return (return_line(fd, bytes));
}

// #include <stdio.h>
// #include <fcntl.h>

// int main(int argc, char **argv)
// {
// 	char *file;
// 	int fd;
// 	char *line;
// 	int cnt;

// 	if (argc != 2)
// 	{
// 		//printf("指定できるファイルは一個です。\n");
// 		return (1);
// 	}
// 	file = argv[1];
// 	fd = open(file, O_RDONLY);
// 	cnt = 0;
// 	while (1)
// 	{
// 		//printf("cnt : %d\n", cnt);
// 		line = get_next_line(fd);
// 		if (line == NULL)
// 		{
// 			printf("\nファイルの読み込みに失敗しました。\n");
// 			return (0);
// 		}
// 		printf("line = %s", line);
// 		cnt++;
// 	}
// 	return (0);
// }

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q a.out");
// }