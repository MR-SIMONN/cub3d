/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash_can.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 17:20:48 by moel-hai          #+#    #+#             */
/*   Updated: 2026/01/06 15:18:22 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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

void	close_fds(void)
{
	int	i;

	i = 3;
	while (i < 1024)
		close (i++);
}

void	free_everything(t_heap *h, int exit_value, int _destroy_mlx)
{
	if (!h)
		return ;
	close_fds();
	if (_destroy_mlx)
		destroy_mlx(configs(0, 0));
	clear_trash(h);
	if (exit_value >= 0)
		exit (exit_value);
}
