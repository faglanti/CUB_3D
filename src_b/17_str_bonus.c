/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17_str_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faglanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:21:08 by faglanti          #+#    #+#             */
/*   Updated: 2022/08/01 13:30:46 by faglanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (!s1[i] && !s2[i])
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_intjoin(t_info *info, t_draw *draw, int num)
{
	int	*tmp;
	int	i;

	if (!draw->objects)
	{
		draw->objects = (int *)malloc(sizeof(int) * 1);
		draw->objects[0] = num;
	}
	else
	{
		i = 0;
		tmp = (int *)malloc(sizeof(int) * (draw->count_objects + 1));
		if (!tmp)
			print_errors(info, 4, NULL);
		while (i < draw->count_objects)
		{
			tmp[i] = draw->objects[i];
			i++;
		}
		tmp[i] = num;
		free (draw->objects);
		draw->objects = tmp;
	}
	draw->count_objects++;
}
