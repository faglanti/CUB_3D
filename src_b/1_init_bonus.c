/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_init_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faglanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:36:03 by faglanti          #+#    #+#             */
/*   Updated: 2022/07/03 15:24:55 by faglanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	init(t_info *info)
{
	info->mlx = NULL;
	info->win = NULL;
	info->list_map = NULL;
	info->list_sprite_images = NULL;
	info->count_sprite_images = 0;
	info->count_sprites = 0;
	info->sprite_textures = NULL;
	info->count_doors = 0;
	info->door_arr = NULL;
	info->player_x = 0;
	info->player_y = 0;
	info->init_dir_x = 0;
	info->init_dir_y = 0;
	info->screen_x = 0;
	info->screen_y = 0;
	inside_init(info);
}

void	inside_init(t_info *info)
{
	info->list_map = NULL;
	info->no = NULL;
	info->so = NULL;
	info->we = NULL;
	info->ea = NULL;
	info->door = NULL;
	info->map_height = 0;
	info->map_width = 0;
	info->map = NULL;
	info->map_activity = 1;
	info->mouse_press = 0;
	info->timer = 0;
}

void	free_all(t_info *info)
{
	if (info->no)
		free(info->no);
	if (info->so)
		free(info->so);
	if (info->we)
		free(info->we);
	if (info->ea)
		free(info->ea);
	if (info->door)
		free(info->door);
	if (info->door_arr)
		free(info->door_arr);
	inside_free_all(info);
}

void	inside_free_all(t_info *info)
{
	int	i;

	if (info->list_sprite_images)
	{
		ft_lstdel(&info->list_sprite_images);
		info->list_sprite_images = NULL;
	}
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
