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
#define BUFFER_SIZE 256
#endif

char	*my_join_line(char *tmp, char *save)
{
	char	*line;
	char	*result;
	int		cnt;

	printf("my_join_line: save = %s\n", save);
	cnt = 0;
	while (tmp[cnt] != '\n')
		cnt++;
	line = (char *)malloc(cnt + 2);
	if (line == NULL)
		return (NULL);
	cnt = 0;
	while (cnt < ft_strlen(tmp))
		line[cnt] = tmp[cnt++];
	line[cnt + 1] = '\0';
	printf("my_join_line: line = %s\n", line);
	result = ft_strjoin(save, line);
	printf("my_join_line: result = %s\n", result);
	free(line);
	return (result);
}

char	*my_return_line(int	i, char *tmp, char *save)
{
	char	*line;
	char	*clone;
	int		cnt;
	size_t	len;

	printf("my_return_line: tmp = %s\n", tmp);
	printf("my_return_line: i = %d\n", i);
	cnt = 0;
	while (tmp[i + cnt] != '\n')
		cnt++;
	printf("my_return_line: cnt = %d\n", cnt);
	clone = (char *)malloc(cnt + 1);
	if (clone == NULL)
		return (NULL);
	cnt = 0;
	while (tmp[i + cnt] != '\n' && tmp[i + cnt] != '\0')
	{
		clone[cnt] = tmp[i + cnt];
		cnt++;
	}
	clone[cnt] = '\n';
	clone[cnt + 1] = '\0';
	printf("my_return_line: clone = %s\n", clone);
	len = ft_strlen(save) + ft_strlen(clone);
	line = (char *)malloc(len + 1);
	if (line == NULL)
		return (NULL);
	line = ft_strjoin(save, clone);
	printf("my_return_line: line = %s\n", line);
	free(clone);
	return (line);
}

//char	*my_join_save(char *tmp, char *save)
//{
//	char	*result;

//	tmp[BUFFER_SIZE] = '\0';
//	result = ft_strjoin(save, tmp);
//	free(save);
//	return (result);
//}

char	*my_strsave(char *buf, int i)
{
	char	*result;
	int		cnt;

	printf("my_strsave: buf = %s\n", buf);
	printf("my_strsave: i = %d\n", i);
	cnt = 0;
	while (buf[i + cnt] != '\n' && buf[i + cnt] != '\0' && i + cnt < BUFFER_SIZE)
		cnt++;
	result = (char *)malloc(cnt + 1);
	if (result == NULL)
		return (NULL);
	cnt = 0;
	while (buf[i] != '\n' && buf[i] != '\0' && i < BUFFER_SIZE)
	{
		result[cnt] = buf[i];
		cnt++;
		i++;
	}
	result[cnt] = '\0';
	printf("my_strsave: result = %s\n", result);
	return (result);
}

char	*my_cpy_buf(char *buf)
{
	char	*result;
	int		cnt;

	cnt = 0;
	while (buf[cnt] != '\0' && cnt < BUFFER_SIZE)
		cnt++;
	result = (char *)malloc(cnt + 1);
	if (result == NULL)
		return (NULL);
	cnt = 0;
	while (buf[cnt] != '\0' && cnt < BUFFER_SIZE)
	{
		result[cnt] = buf[cnt];
		cnt++;
	}
	result[cnt] = '\0';
	printf("my_cpy_buf: result = %s\n", result);
	return (result);
}

char	*new_get_next_line(int fd)
{
	char			buf[BUFFER_SIZE + 1];
	static int		bytes;
	//t_list			node;
	//static t_list	*str = NULL;
	static int		i = 0;
	int				pos;
	static char		*tmp;
	static char		*save = "";
	char			*result;

	i = 0;
	while (i <= BUFFER_SIZE)
	{
		buf[i] = '\0';
		i++;
	}
	i = 0;
	if (0 < i)
	{
		printf("save = \"\"\n");
		save = "";
	}
	pos = i;
	//ファイルの終端に達するまでループ
	while (1)
	{
		printf("while (1): i = %d\n", i);
		printf("while (1): save = %s\n", save);
		//読み込む
		if (i == 0)
		{
			bytes = read(fd, buf, BUFFER_SIZE);
			tmp = my_cpy_buf(buf);
		}
		printf("while (1): bytes = %d\n", bytes);
		printf("while (1): buf = %s\n", buf);
		if (bytes <= 0)
		{
			printf("終端\n");
			break ;
		}
		// printf("bytes = %d\n", BUFFER_SIZE);
		//bufの改行チェック
		//tmp_i = 0;
		while (i < BUFFER_SIZE)
		{
			printf("while: i = %d\n", i);
			if (tmp[i] == '\n')
			{
				//改行が入っていた場合はreturn
				//tmp[tmp_i] = buf[i];
				//tmp[tmp_i + 1] = '\0';
				result = my_return_line(pos, tmp, save);
				while (tmp[i] == '\n')
					i++;
				printf("while: tmp = %s\n", tmp);
				save = my_strsave(tmp, i);
				//if (bytes == BUFFER_SIZE)
				//	i = 0;
				return (result);
			}
			else if (tmp[i] == '\0')
			{
				result = my_return_line(pos, tmp, save);
				printf("while: tmp = %s\n", tmp);
				save = my_strsave(tmp, i);
				//i = 0;
				return (result);
			}
			i++;
			//tmp_i++;
		}
		//bufに改行が入っていなかった場合 = リストにsaveを追加
		//str = (t_list *)malloc(sizeof(t_list));
		//if (str == NULL)
		//	return (NULL);
		//save[BUFFER_SIZE] = '\0';
		//printf("save = %s\n", tmp);
		//node.content = tmp;
		//node.next = NULL;
		////i = 0
		//i = 0;
		//ft_lstadd_back(&str, &node);
		//printf("o\n");
		
		//bufに改行が入っていなかった場合、strjoinでsaveに連結
		save = ft_strjoin(save, buf);
		printf("save = %s\n", save);
		i = 0;
	}
	if (save[0] != '\0')
	{
		result = save;
		save = "";
		return (result);
	}
	else
		return (NULL);
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
		 printf("\x1b[34m%d回目のget_next_line\x1b[m\n", cnt + 1);
		line = new_get_next_line(fd);
		if (line == NULL)
		{
			// printf("ファイルの読み込みに失敗しました。\n");
			return (0);
		}
		printf("\x1b[32m%s\x1b[m", line);
		free(line);
		cnt++;
	}
	return (0);
}
