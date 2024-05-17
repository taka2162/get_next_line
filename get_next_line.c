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
#define BUFFER_SIZE 100
#endif

char *return_result(char **save)
{
	char *result;
	char *new_save;
	int cnt;
	int i;

	//printf("\x1b[35m---return_result---\n");

	if (*save == NULL)
		return (NULL);
	cnt = 0;
	while ((*save)[cnt] != '\n' && (*save)[cnt] != '\0')
	{
		cnt++;
	}

	// //printf("cnt\t=\t%d\n", cnt);

	if ((*save)[cnt] == '\0')
	{
		// result = *save;
		// free(*save);
		// *save = "";
		return (*save);
	}
	result = (char *)malloc(cnt + 2);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i <= cnt)
	{
		result[i] = (*save)[i];
		i++;
	}
	result[i] = '\0';

	//printf("result\t=\t%s\n", result);

	while ((*save)[cnt] != '\0')
		cnt++;
	new_save = (char *)malloc(cnt - i + 1);
	if (new_save == NULL)
	{
		free(result);
		return (NULL);
	}

	// //printf("cnt-i+1\t=\t%d\n", cnt - i + 1);

	cnt = 0;
	while ((*save)[i + cnt] != '\0')
	{
		// //printf("cnt\t=\t%d\n", cnt);
		// //printf("(*save)[i+cnt]\t=\t%c\n", (*save)[i+cnt]);

		new_save[cnt] = (*save)[i + cnt];
		cnt++;
	}
	// //printf("cnt = %d\n", cnt);
	new_save[cnt] = '\0';

	// //printf("new_save\t=\t%s\n", new_save);

	if (save[0] != '\0')
		free(*save);
	*save = new_save;

	//printf("----------\x1b[m\n");

	return (result);
}

char *return_line(int fd, char *buf)
{
	static char *save = "";
	char *tmp;
	char *result;
	int bytes;

	//printf("\x1b[32m---return_line---\n");

	//printf("save\t=\t%s\n", save);
	bytes = 0;
	while (1)
	{
		if (ft_strchr(save, '\n') == NULL)
		{
			bytes = read(fd, buf, BUFFER_SIZE);

			buf[bytes] = '\0';
			//printf("buf\t=\t%s\n", buf);
			//printf("bytes\t=\t%d\n", bytes);

			tmp = save;
			save = ft_strjoin(tmp, buf);
			if (save == NULL)
				return (NULL);
			if (tmp[0] != '\0')
			{
				free(tmp);
				tmp = NULL;
			}
			if (bytes <= 0)
			{
				break;
			}
		}
		if (ft_strchr(save, '\n') != NULL)
		{
			//printf("save\t=\t%s\n", save);

			result = return_result(&save);
			if (result == NULL)
				return (NULL);

			//printf("\x1b[32m");
			//printf("save\t=\t%s\n", save);
			//printf("result\t=\t%s\n", result);
			//printf("----------\x1b[m\n");
			//printf("return (result)\n");

			return (result);
		}
	}

	//printf("----------\x1b[m\n");

	if (save[0] != '\0')
	{
		tmp = save;
		if (save[0] != '\0')
		{
			free(save);
			save = "";
		}
		return (tmp);
	}
	return (NULL);
}

char *get_next_line(int fd)
{
	char buf[BUFFER_SIZE + 1];

	//printf("buf = %s\n", buf);
	return (return_line(fd, buf));
}

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
// 			//printf("\nファイルの読み込みに失敗しました。\n");
// 			return (0);
// 		}
// 		//printf("line = %s", line);
// 		cnt++;
// 	}
// 	return (0);
// }
