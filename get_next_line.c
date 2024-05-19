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
#define BUFFER_SIZE 10
#endif

char *return_result(char **save)
{
	char *result;

	//printf("\x1b[35m---return_result---\n");

	if (*save == NULL)
		return (NULL);
	// cnt = 0;
	// while ((*save)[cnt] != '\n' && (*save)[cnt] != '\0')
	// {
	// 	cnt++;
	// }
	char *new_line_pos = ft_strchr(*save, '\n');
	*new_line_pos = '\0';
	result = (char *)malloc(ft_strlen(*save) + 2);
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, *save, ft_strlen(*save));
	result[ft_strlen(*save) + 1] = '\0';
	result[ft_strlen(*save)] = '\n';

	//	//printf("cnt\t=\t%d\n", cnt);

	// if ((*save)[cnt] == '\0')
	// {
	// 	result = *save;
	// 	free(*save);
	// 	*save = "";
	// 	return (result);
	// }


	// result = (char *)malloc(cnt + 2);
	// if (result == NULL)
	// 	return (NULL);
	// i = 0;
	// while (i <= cnt)
	// {
	// 	result[i] = (*save)[i];
	// 	i++;
	// }
	// result[i] = '\0';

	//printf("result\t=\t%s\n", result);

	char	*tmp_change;
	tmp_change = ft_strdup(++new_line_pos);
	if (tmp_change == NULL)
	{
		free(result);
		return (NULL);
	}
	free(*save);
	*save = tmp_change;
	//printf("*save = %s\n", *save);

	// while ((*save)[cnt] != '\0')
	// 	cnt++;
	// new_save = (char *)malloc(cnt - i + 1);
	// if (new_save == NULL)
	// {
	// 	//printf("free(result)\n");
	// 	return (free(result), NULL);
	// }

	// //	//printf("cnt-i+1\t=\t%d\n", cnt - i + 1);

	// cnt = 0;
	// while ((*save)[i + cnt] != '\0')
	// {
	// 	//	//printf("cnt\t=\t%d\n", cnt);
	// 	//	//printf("(*save)[i+cnt]\t=\t%c\n", (*save)[i+cnt]);

	// 	new_save[cnt] = (*save)[i + cnt];
	// 	cnt++;
	// }
	// //	//printf("cnt = %d\n", cnt);
	// new_save[cnt] = '\0';

	// //	//printf("new_save\t=\t%s\n", new_save);

	// // //printf("free(*save)\n");
	// // //printf("*save\t=\t%s\n", *save);
	// free(*save);
	// *save = new_save;

	//printf("----------\x1b[m\n");

	return (result);
}

char	*return_line(int fd, char *tmp, char *result, int bytes)
{
	char		*buf;
	static char	*save = NULL;
	// char		*start_pos;

	//printf("\x1b[32m---return_line---\n");

	// if (save == NULL)
	// {
	// 	save = (char *)malloc(1);
	// 	if (save == NULL)
	// 		return (NULL);
	// 	*save = '\0';
	// }
	buf = NULL;
	// start_pos = NULL;
	//printf("save\t=\t%s\n", save);
	while (1)
	{
		if (ft_strchr(save, '\n') == NULL)
		{
			buf = (char *)malloc(BUFFER_SIZE + 1);
			if (buf == NULL)
				return (NULL);
			bytes = read(fd, buf, BUFFER_SIZE);

			//printf("buf\t=\t%s\n", buf);
			//printf("bytes\t=\t%d\n", bytes);

			if (bytes <= 0)
				break;
			buf[bytes] = '\0';
			if (save == NULL)
			{
				//printf("\x1b[36mif (save == NULL)\n");
				save = (char *)malloc(bytes + 1);
				if (save == NULL)
					return (NULL);
				// save = buf;
				// start_pos = save;
				//printf("save = %s\n", save);
				ft_memcpy(save, buf, bytes + 1);
				free(buf);
				//printf("\x1b[32m");
			}
			else
			{
				//printf("\x1b[36melse\n");
				//printf("save = %s\n", save);
				tmp = ft_strjoin(save, buf);
				if (tmp == NULL)
				{
					free(buf);
					free(save);
					// free(start_pos);
					buf = NULL;
					save = NULL;
					// start_pos = NULL;
					return (NULL);
				}
				//printf("buf = %s\n", buf);
				// //printf("start_pos = %s\n", start_pos);
				free(buf);
				//printf("free(buf)\n");
				buf = NULL;
				// free(start_pos);
				// //printf("free(start_pos)\n");
				// start_pos = NULL;
				if (save != NULL)
					free(save);
				//printf("tmp = %s\n", tmp);
				save = tmp;
				// start_pos = save;
				//printf("\x1b[32m");
			}
		}
		if (ft_strchr(save, '\n') != NULL)
		{
			//printf("save\t=\t%s\n", save);

			result = return_result(&save);
			
			//printf("\x1b[32m");
			//printf("save\t=\t%s\n", save);
			//printf("result\t=\t%s\n", result);
			//printf("return (result)\n");
			// free(buf);
			//printf("free(buf)\n");
			// buf = NULL;
			// free(start_pos);
			//printf("free(start_pos)\n");
			// start_pos = NULL;
			//printf("----------\x1b[m\n");
			return (result);
		}
	}

	if (bytes == -1)
	{
		free(save);
		free(buf);
		save = NULL;
		buf = NULL;
		return (NULL);
	}
	if (save != NULL)
	{
		if (*save == '\0')
		{
			free(save);
			save = NULL;
		}
		tmp = save;
		save = NULL;
		//printf("tmp = %s\n", tmp);
		free(buf);
		// free(start_pos);
		buf = NULL;
		// start_pos = NULL;
		//printf("----------\x1b[m\n");
		return (tmp);
	}

	//printf("buf = %s\n", buf);
	// //printf("start_pos = %s\n", start_pos);
	free(buf);
	free(save);
	save = NULL;
	// free(start_pos);
	buf = NULL;
	// start_pos = NULL;
	//printf("----------\x1b[m\n");
	return (NULL);
}

char *get_next_line(int fd)
{
	char	*tmp;
	char	*result;
	int		bytes;

	if (BUFFER_SIZE >= INT_MAX)
		return (NULL);
	tmp = NULL;
	result = NULL;
	bytes = 0;
	return (return_line(fd, tmp, result, bytes));
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