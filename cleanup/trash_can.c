/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash_can.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 17:20:48 by moel-hai          #+#    #+#             */
/*   Updated: 2025/10/25 17:59:26 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	clear_trash(t_heap *lst)
{
	t_heap	*temp;

	if (lst == NULL)
		return ;
	while (lst)
	{
		temp = lst->next;
		free(lst->address);
		lst->address = NULL;
		free(lst);
		lst = temp;
	}
}

void	free_everything(t_heap *h, int exit)
{
	if (!h)
		return ;
	clear_trash(h);
    if (exit >= 0)
        exit (exit);
}
