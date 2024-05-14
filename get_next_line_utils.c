/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:34:10 by ttakino           #+#    #+#             */
/*   Updated: 2024/05/14 16:46:37 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_len_to_x(const char *str, char x)
{
	size_t	i;

	i = 0;
	while (str[i] != x && str[i] != '\0')
		i++;
	return (i);
}

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

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;
	t_list	*current;

	if (lst == NULL || del == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		del(current->content);
		free(current);
		current = next;
	}
	*lst = NULL;
}

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
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
