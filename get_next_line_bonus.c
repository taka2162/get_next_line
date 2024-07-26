/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:46:55 by ttakino           #+#    #+#             */
/*   Updated: 2024/07/26 18:40:18 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*update_save(char *save[OPEN_MAX], char **buf, int bytes)
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

char	*generate_line(char *save[OPEN_MAX])
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

char	*on_reading_failed(char **buf, char *save[OPEN_MAX], int bytes)
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
	static char	*save[OPEN_MAX] = {NULL};

	if (fd < 0 || OPEN_MAX < fd)
		return (NULL);
	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (NULL);
	bytes = 0;
	while (ft_strchr(save[fd], '\n') == NULL)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes <= 0)
			return (on_reading_failed(&buf, &save[fd], bytes));
		buf[bytes] = '\0';
		save[fd] = update_save(&save[fd], &buf, bytes);
		if (!save[fd])
			break ;
	}
	free(buf);
	buf = NULL;
	return (generate_line(&save[fd]));
}

// #include <stdio.h>
// #include <fcntl.h>

// int main(int argc, char **argv)
// {
// 	int		fd_list[argc - 1];
// 	int		n;
// 	int		check_null[argc - 1];
// 	char	*line;

// 	n = 0;
// 	while (n < argc - 1)
// 		check_null[n++] = 1;
// 	n = 0;
// 	line = "";
// 	while (n < argc - 1)
// 	{
// 		fd_list[n] = open(argv[n + 1], O_RDONLY);
// 		n++;
// 	}
// 	while (1)
// 	{
// 		n = 0;
// 		while (n < argc - 1)
// 		{
// 			line = get_next_line(fd_list[n]);
// 			if (!line)
// 				break ;
// 			printf("fd[%d]: %s\n", n + 1, line);
// 			free(line);
// 			n++;
// 		}
// 		if (!line && check_null[n] != 0)
// 		{
// 			check_null[n] = 0;
// 			n = 0;
// 			while (check_null[n] == 0)
// 				n++;
// 			if (n == argc - 1)
// 				break ;
// 		}
// 	}
// 	return (0);
// }

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q a.out");
// }
