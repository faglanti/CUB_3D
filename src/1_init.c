/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faglanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:36:03 by faglanti          #+#    #+#             */
/*   Updated: 2022/07/03 18:02:59 by faglanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	init(t_info *info)
{
	info->mlx = NULL;
	info->win = NULL;
	info->list_map = NULL;
	info->player_x = 0;
	info->player_y = 0;
	info->init_dir_x = 0;
	info->init_dir_y = 0;
	info->screen_x = 0;
	info->screen_y = 0;
	info->list_map = NULL;
	info->no = NULL;
	info->so = NULL;
	info->we = NULL;
	info->ea = NULL;
	info->map_height = 0;
	info->map_width = 0;
	info->map = NULL;
}

void	free_all(t_info *info)
{
	int	i;

	if (info->no)
		free(info->no);
	if (info->so)
		free(info->so);
	if (info->we)
		free(info->we);
	if (info->ea)
		free(info->ea);
	if (info->list_map)
	{
		ft_lstdel(&info->list_map);
		info->list_map = NULL;
	}
	if (info->map)
	{
		i = 0;
		while (info->map[i])
			free(info->map[i++]);
		free(info->map);
	}
}

int	quit(t_info *info)
{
	mlx_destroy_window(info->mlx, info->win);
	free_all(info);
	exit(0);
}
