/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_collecting_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 19:39:49 by ielouarr          #+#    #+#             */
/*   Updated: 2025/10/25 18:37:25 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char **get_rgb(char *rgbline, t_config *cfg)
{
    int i = 0;
    int component;
    char **rgb = ft_malloc(sizeof(char *) * 4, cfg);

    while(rgbline[i] == 32 || rgbline[i] == 9)
	{
        i++;
	}
	component = 0;
	while (component < 3)
	{
		int  value = 0;
		int  count = 0;
		if (rgbline[i] < '0' || rgbline[i] > '9')
			return NULL;
		while (rgbline[i] >= '0' && rgbline[i] <= '9')
		{
			value = value * 10 + (rgbline[i] - '0');
			count++;
			i++;
		}
		if (count == 0 || value > 255)
			return NULL;
		while (rgbline[i] == ' ' || rgbline[i] == '\t')
			i++;
		if (component < 2  && rgbline[i++] != ',')
			return NULL;
		while (rgbline[i] == ' ' || rgbline[i] == '\t')
			i++;
        rgb[component] = ft_itoa(value, cfg);
		component++;
	}
    if(component != 3)
        return NULL;
    rgb[component] = NULL;
    return rgb;
}