/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:46:55 by ttakino           #+#    #+#             */
/*   Updated: 2024/05/20 17:28:42 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*generate_new_save(char *save[OPEN_MAX], char **buf, int bytes)
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

char	*generate_line(char *save[OPEN_MAX])
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

char	*end_of_loop(char **buf, char *save[OPEN_MAX], int bytes)
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
	static char	*save[OPEN_MAX] = {NULL};

	buf = NULL;
	while (1)
	{
		if (ft_strchr(save[fd], '\n') == NULL)
		{
			buf = (char *)malloc(BUFFER_SIZE + 1);
			if (buf == NULL)
				return (NULL);
			bytes = read(fd, buf, BUFFER_SIZE);
			if (bytes <= 0)
				break ;
			buf[bytes] = '\0';
			save[fd] = generate_new_save(&save[fd], &buf, bytes);
		}
		if (ft_strchr(save[fd], '\n') != NULL)
			return (generate_line(&save[fd]));
	}
	return (end_of_loop(&buf, &save[fd], bytes));
}

char	*get_next_line(int fd)
{
	int		bytes;

	if (BUFFER_SIZE < 0 || INT_MAX < BUFFER_SIZE || fd < 0 || 1024 < fd)
		return (NULL);
	bytes = 0;
	return (return_line(fd, bytes));
}

// #include <stdio.h>
// #include <fcntl.h>

// int main(int argc, char **argv)
// {
// 	char f;
// 	int fd;
// 	char *line;
// 	int cnt;

// 	if (argc < 2)
// 	{
// 		//printf("指定できるファイルは一個です。\n");
// 		return (1);
// 	}
// 	f = 1;
// 	printf("\n");
// 	while (f < argc)
// 	{
// 		fd = open(argv[f], O_RDONLY);
// 		cnt = 0;
// 		while (1)
// 		{
// 			//printf("cnt : %d\n", cnt);
// 			line = get_next_line(fd);
// 			if (line == NULL)
// 			{
// 				printf("\n%d個目のファイルの読み込み終了。\n\n", f);
// 				break ;
// 			}
// 			printf("line = %s", line);
// 			cnt++;
// 		}
// 		f++;
// 	}
// 	return (0);
// }

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q a.out");
// }
