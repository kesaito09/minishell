/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_path_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 01:57:39 by kesaitou          #+#    #+#             */
/*   Updated: 2026/04/19 22:00:00 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/main.h"

static size_t	count_words(const char *s, char c);
static char		*alloc_string(char const *str, char c, t_shared_info *info);

char	**path_split(char const *s, char c, t_shared_info *info)
{
	char	**arr;
	int		i;

	if (!s)
		return (NULL);
	arr = ft_calloc(count_words(s, c) + 1, sizeof(char *));
	if (!arr)
		child_fatal_exit(info);
	i = 0;
	while (*s)
	{
		arr[i++] = alloc_string(s, c, info);
		while (*s && *s != c)
			s++;
		if (*s && *s == c)
			s++;
	}
	return (arr);
}

static size_t	count_words(const char *s, char c)
{
	size_t	count;

	if (!s || !*s)
		return (0);
	count = 1;
	while (*s)
	{
		if (*s == c)
			count++;
		s++;
	}
	return (count);
}

static char	*alloc_string(char const *str, char c, t_shared_info *info)
{
	size_t	i;
	size_t	len;
	char	*arr;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	if (len == 0)
	{
		arr = ft_strdup("./");
		if (!arr)
			child_fatal_exit(info);
		return (arr);
	}
	arr = ft_calloc(len + 1, sizeof(char));
	if (!arr)
		child_fatal_exit(info);
	i = 0;
	while (i < len)
	{
		arr[i] = str[i];
		i++;
	}
	return (arr);
}
