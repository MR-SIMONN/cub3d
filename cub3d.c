/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:30:21 by ielouarr          #+#    #+#             */
/*   Updated: 2025/11/25 12:33:32 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char **av)
{
    t_config configs;
    int fd;
    int ret;

    if (ac != 2)
        return(printf("Cub3d : Invalid args [./cub3d your_map]"), 1);
    if (ft_strnstr(av[1], ".cub", ft_strlen(av[1])))
        return(printf("Cub3d : Wrong map name [your_map`.cub`]"), 1);
    fd = open(av[1], O_RDONLY);
    if(fd < 0)
        return (printf("Cub3d : can't access the file map"), 1);
    close(fd);
    init_config(&configs);
    if(check_validmap(av[1], &configs))
        return(printf("Cub3d : invalid map"), free_everything(g_c(0, 0), -1), 1);
    ret = mapcollecting(&configs, av[1]);
    if(ret)
    {
        free_everything(g_c(0, 0), -1);
        return(printf("Cub3d : invalid map"), 1);
    }

    // ray casting and textures :)
    
    free_everything(g_c(0, 0), -1);
    return (0);
}
