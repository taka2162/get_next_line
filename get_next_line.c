/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:34:07 by ttakino           #+#    #+#             */
/*   Updated: 2024/07/26 18:50:30 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*update_save(char **save, char **buf, int bytes)
{
	char	*tmp;

	if (*save == NULL)
	{
		tmp = (char *)malloc(bytes + 1);
		if (tmp == NULL)
			return (NULL);
		ft_memcpy(tmp, *buf, bytes + 1);
		*save = tmp;
		return (*save);
	}
	else
	{
		tmp = ft_strjoin(*save, *buf);
		if (tmp == NULL)
			return (free(*save), *save = NULL, NULL);
		return (free(*save), tmp);
	}
}

char	*generate_line(char **save)
{
	char	*result;
	char	*new_line_pos;
	char	*tmp;

	if (*save == NULL)
		return (NULL);
	new_line_pos = ft_strchr(*save, '\n');
	*new_line_pos = '\0';
	result = ft_strjoin(*save, "\n");
	if (result == NULL)
		return (free(*save), *save = NULL, NULL);
	tmp = ft_strdup(new_line_pos + 1);
	if (tmp == NULL)
	{
		free(result);
		return (NULL);
	}
	free(*save);
	*save = tmp;
	return (result);
}

char	*on_reading_failed(char **buf, char **save, int bytes)
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
		*save = NULL;
		return (free(*buf), *buf = NULL, tmp);
	}
	return (free(*buf), free(*save), *buf = NULL, *save = NULL, NULL);
}

char	*get_next_line(int fd)
{
	char		*buf;
	int			bytes;
	static char	*save = NULL;

	if (fd < 0 || OPEN_MAX < fd)
		return (NULL);
	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (NULL);
	bytes = 0;
	while (ft_strchr(save, '\n') == NULL)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes <= 0)
			return (on_reading_failed(&buf, &save, bytes));
		buf[bytes] = '\0';
		save = update_save(&save, &buf, bytes);
		if (!save)
			break ;
	}
	free(buf);
	buf = NULL;
	return (generate_line(&save));
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
// 		return (1);
// 	file = argv[1];
// 	fd = open(file, O_RDONLY);
// 	cnt = 0;
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (line == NULL)
// 		{
// 			printf("\nファイルの終端に達しました。\n");
// 			return (0);
// 		}
// 		printf("%s", line);
// 		free(line);
// 		cnt++;
// 	}
// 	return (0);
// }

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q a.out");
// }
