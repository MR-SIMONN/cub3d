/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:18:48 by ielouarr          #+#    #+#             */
/*   Updated: 2026/01/10 10:55:32 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strlen(char *senc)
{
	int	i;

	i = 0;
	while (senc[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t ncmp)
{
	size_t	i;

	i = 0;
	while (i < ncmp && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	if (i < ncmp && (s1[i] || s2[i]))
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

int	ft_strnstr(char *haystack, char *needle, size_t len)
{
	size_t	needle_len;
	size_t	i;

	needle_len = ft_strlen(needle);
	if (len == 0)
		return (1);
	i = 0;
	while ((i <= len - needle_len) && haystack[i] != '\0')
	{
		if (len < needle_len)
			return (1);
		if (ft_strncmp(&haystack[i], needle, needle_len) == 0)
		{
			return (0);
		}
		i++;
	}
	return (1);
}
