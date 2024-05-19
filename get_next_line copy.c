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

void	initialize_arr(char *arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		*arr = '\0';
		arr++;
		i++;
	}
}

char	*return_result(char **save)
{
	char	*result;
	char	*newSave;
	int		cnt;
	int		i;

	printf("\x1b[35m---return_result---\n");

	if (save == NULL || *save == NULL)
		return (NULL);
	cnt = 0;
	while ((*save)[cnt] != '\n' && (*save)[cnt] != '\0')
	{
		cnt++;
	}
	
	// printf("cnt\t=\t%d\n", cnt);

	if ((*save)[cnt] == '\0')
		return (*save);
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
	
	printf("result\t=\t%s\n", result);

	while ((*save)[cnt] != '\0')
		cnt++;
	newSave = (char *)malloc(cnt - i + 1);
	if (newSave == NULL)
	{
		free(result);
		return (NULL);
	}

	// printf("cnt-i+1\t=\t%d\n", cnt - i + 1);

	cnt = 0;
	while ((*save)[i + cnt] != '\0')
	{
		// printf("cnt\t=\t%d\n", cnt);
		// printf("(*save)[i+cnt]\t=\t%c\n", (*save)[i+cnt]);

		newSave[cnt] = (*save)[i + cnt];
		cnt++;
	}

	printf("newSave\t=\t%s\n", newSave);

	free(*save);
	*save = newSave;

	printf("----------\x1b[m\n");

	return (result);
}

void	set_next(char *next, char *buf)
{
	int			i;
	int			next_i;
	int			flag;

	//printf("\x1b[31m---set_next---\n");
	if (ft_strchr(next, '\n') != NULL || buf[0] == '\0')
	{
		i = 0;
		next_i = 0;
		while (next[i] != '\n')
			i++;
		if (next[i] == '\n')
			i++;
		while (i + next_i < BUFFER_SIZE && next[i] != '\n')
		{
			next[next_i] = next[i + next_i];
			next_i++;
		}
		next[i + next_i] = '\0';
		//printf("if: i\t=\t%d\nnext_i\t=\t%d\nnext\t=\t%s\n", i, next_i, next);
		//printf("----------\x1b[m\n");
		return ;
	}
	initialize_arr(next, BUFFER_SIZE);
	i = 0;
	next_i = 0;
	flag = 0;
	while (i < BUFFER_SIZE && buf[i] != '\0')
	{
		if (flag == 1)
		{
			next[next_i] = buf[i];
			next_i++;
		}
		if (buf[i] == '\n')
			flag = 1;
		i++;
	}
	//printf("next\t=\t%s\n", next);
	//printf("----------\x1b[m\n");
}

char	*return_line(int fd, char *buf)
{
	static char	*save = "";
	char		*tmp;
	char		*result;
	int			bytes;

	printf("\x1b[32m---return_line---\n");

	printf("save\t=\t%s\n", save);
	bytes = 0;
	while (1)
	{
		if (ft_strchr(save, '\n') == NULL)
		{
			bytes = read(fd, buf, BUFFER_SIZE);

			printf("buf\t=\t%s\n", buf);
			printf("bytes\t=\t%d\n", bytes);

			buf[bytes] = '\0';
			tmp = save;
			save = ft_strjoin(tmp, buf);
			if (save == NULL)
				return (NULL);
			if (tmp[0] != '\0')
				free(tmp);
			tmp = NULL;
			if (bytes <= 0)
			{
				break;
			}
		}
		// if (0 < bytes && bytes == BUFFER_SIZE && ft_strchr(buf, '\n') == NULL)
		// {
		// 	save = ft_strjoin(save, buf);
		// 	if (save == NULL)
		// 		return (NULL);
		// 	//printf("if: save\t=\t%s\n", save);
		// }
	
		printf("save\t=\t%s\n", save);

		result = return_result(&save);
		if (result == NULL)
			return (NULL);

		printf("\x1b[32m");
		printf("save\t=\t%s\n", save);
		//printf("next\t=\t%s\n", next);
		// set_next(next, buf);
		// save = ft_strjoin(next, "");
		//printf("save\t=\t%s\n", save);
		// if (save == NULL)
		// 	return (NULL);
		printf("result\t=\t%s\n", result);
		printf("----------\x1b[m\n");
		if (ft_strchr(result, '\n') != NULL)
			return (result);
	
		// initialize_arr(buf, BUFFER_SIZE);
	}
	//printf("save = %s\n", save);
	printf("----------\x1b[m\n");

	// if (save[0] != '\0')
	// {
	// 	tmp = save;
	// 	save = "";
	// 	return (tmp);
	// }
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE];
	// static char	next[BUFFER_SIZE] = "";

	// initialize_arr(buf, BUFFER_SIZE + 1);
	// //printf("buf\t=\t%s\n", buf);
	return (return_line(fd, buf));
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
			printf("\nファイルの読み込みに失敗しました。\n");
			return (0);
		}
		printf("line = %s", line);
		free(line);
		cnt++;
	}
	return (0);
}
