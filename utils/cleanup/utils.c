/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 17:34:10 by moel-hai          #+#    #+#             */
/*   Updated: 2025/11/25 12:19:19 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

t_heap	*g_c(int should_update,	t_heap *new_value)
{
	static t_heap	*h;

	if (should_update)
		h = new_value;
	return (h);
}

void	ft_lstadd_front(t_heap **lst, t_heap *p)
{
	if (!p || !lst)
		return ;
	p->next = *lst;
	*lst = p;
}

void	*ft_malloc(size_t size, t_config *d)
{
	void	*allocated;
	t_heap	*p;

	if (!d)
		return (NULL);
	p = malloc(sizeof(t_heap));
	if (!p)
	{
		ft_putstr_fd("unexpected error with malloc\n", 2);
		free_everything(d->garbage, 1);
	}
	allocated = malloc(size);
	if (!allocated)
	{
		ft_putstr_fd("unexpected error with malloc\n", 2);
		free(p);
		free_everything(d->garbage, 1);
	}
	p->address = allocated;
	p->next = NULL;
	ft_lstadd_front(&d->garbage, p);
    g_c(1, d->garbage);
	return (allocated);
}
