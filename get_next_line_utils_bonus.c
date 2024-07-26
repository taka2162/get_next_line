/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:46:31 by ttakino           #+#    #+#             */
/*   Updated: 2024/07/26 18:40:39 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*cast_dst;
	const unsigned char	*cast_src;

	if (dest == NULL && src == NULL)
		return (NULL);
	cast_dst = (unsigned char *)dest;
	cast_src = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		*cast_dst++ = *cast_src++;
		i++;
	}
	return (dest);
}

char	*ft_strchr(const char *str, int c)
{
	int				i;
	unsigned char	cst_c;

	if (str == NULL)
		return (NULL);
	cst_c = (unsigned char)c;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == cst_c)
			return ((char *)&str[i]);
		i++;
	}
	if (cst_c == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	i;
	size_t	s1_size;
	size_t	s2_size;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	result = (char *)malloc((s1_size + s2_size + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < s1_size || i <= s2_size)
	{
		if (i < s1_size)
			result[i] = s1[i];
		if (i <= s2_size)
		result[s1_size + s2_size - i] = s2[s2_size - i];
		i++;
	}
	return (result);
}

char	*ft_strdup(const char *string)
{
	int		size;
	char	*result;
	int		i;

	i = 0;
	size = ft_strlen(string) + 1;
	result = (char *)malloc(size * sizeof(char));
	if (result == NULL)
		return (NULL);
	while (string[i] != '\0')
	{
		result[i] = string[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
