/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_lists.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faglanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:12:40 by faglanti          #+#    #+#             */
/*   Updated: 2022/07/03 18:04:34 by faglanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_list **begin, t_list *new)
{
	t_list	*tmp;

	if (new)
	{
		tmp = *begin;
		if (!tmp)
			*begin = new;
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
}

void	ft_lstdelone(t_list *list, void (*del)(void *))
{
	if (list != NULL && del != NULL)
		del(list->content);
	free(list);
}

void	ft_lstclear(t_list **begin, void (*del)(void *))
{
	if (*begin != NULL)
	{
		ft_lstclear(&(*begin)->next, del);
		ft_lstdelone(*begin, del);
		*begin = NULL;
	}
}

void	ft_lstdel(t_list **begin)
{
	if (!begin || !*begin)
		return ;
	ft_lstdel(&(*begin)->next);
	free((*begin)->content);
	free(*begin);
	*begin = NULL;
}
