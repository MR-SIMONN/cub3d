/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:18:48 by ielouarr          #+#    #+#             */
/*   Updated: 2025/10/14 15:43:03 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	 ft_strnstr(char *haystack, char *needle, size_t len)
{
	size_t	needle_len;
	size_t	i;

	needle_len = ft_strlen(needle);
	if (len == 0)
		return 1;
	i = 0;
	while ((i <= len - needle_len) && haystack[i] != '\0')
	{
		if (len < needle_len)
			return 1;
		if (ft_strncmp(&haystack[i], needle, needle_len) == 0)
		{
			return 0;
		}
		i++;
	}
	return 1;
}