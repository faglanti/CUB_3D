/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_minimap_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faglanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:24:48 by faglanti          #+#    #+#             */
/*   Updated: 2022/08/01 13:25:44 by faglanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	draw_minimap(t_info *info)
{
	int	i;
	int	j;

	draw_map_pixels(info, (int)info->player_x, (int)info->player_y, 2);
	j = -1;
	while (info->map[++j])
	{
		i = -1;
		while (info->map[j][++i])
		{
			if (info->map[j][i] == '1')
				draw_map_pixels(info, i, j, 1);
		}
	}
}

void	draw_map_pixels(t_info *info, int i, int j, int flag)
{
	t_map	map;

	map.flag = flag;
	if (flag == 1)
	{
		map.color = 0x00700000;
		map.i_start = (i + 1) * PIXELS_ON_UNIT - 1;
		map.i_end = (i + 2) * PIXELS_ON_UNIT;
		if (map.i_end + 1 > WIDTH)
			map.i_end = WIDTH - PIXELS_ON_UNIT - 1;
	}
	if (flag == 2)
	{
		map.color = 0x00FF0000;
		map.i_start = round((1 + info->player_x) * PIXELS_ON_UNIT)
			- PIXELS_ON_UNIT / 2 - 1 - 1;
		map.i_end = map.i_start + 1 + PIXELS_ON_UNIT / 2 + 2;
		if (map.i_end + 1 > WIDTH)
			map.i_end = WIDTH - 1;
	}
	inside1_draw_map_pixel(info, &map, i, j);
}

void	inside1_draw_map_pixel(t_info *info, t_map *map, int i, int j)
{
	while (++map->i_start < map->i_end)
	{
		if (map->flag == 1)
		{
			map->j_start = (j + 1) * PIXELS_ON_UNIT - 1;
			map->j_end = (j + 2) * PIXELS_ON_UNIT;
			if (map->j_end + 1 > HEIGHT)
				map->j_end = (int)(HEIGHT / PIXELS_ON_UNIT - 2);
		}
		if (map->flag == 2)
		{
			map->j_start = round((1 + info->player_y) * PIXELS_ON_UNIT)
				- PIXELS_ON_UNIT / 2 - 1 - 1;
			map->j_end = map->j_start + 1 + PIXELS_ON_UNIT / 2 + 2;
			if ((map->j_end + 1) > HEIGHT)
				map->j_end = (int)(HEIGHT / PIXELS_ON_UNIT - 2);
		}
		while (++map->j_start < map->j_end)
			my_mlx_pixel_put(&info->picture, map->i_start,
				map->j_start, map->color);
	}
	inside2_draw_map_pixel(info, map, i, j);
}

void	inside2_draw_map_pixel(t_info *info, t_map *map, int i, int j)
{
	if (map->flag == 1)
	{
		if (j == info->map_height - 1 || ft_strlen(info->map[j + 1]) <= i
			|| info->map[j + 1][i] != '1')
		{
			map->i_start = (i + 1) * PIXELS_ON_UNIT - 1;
			map->i_end = map->i_start + 1 + PIXELS_ON_UNIT;
			if (map->i_end + 1 > WIDTH)
				map->i_end = WIDTH - 1;
			map->j_start = (j + 2) * PIXELS_ON_UNIT - PIXELS_ON_UNIT / 3;
			map->j_end = map->j_start + PIXELS_ON_UNIT / 3;
			if (map->j_end + 1 > HEIGHT)
				map->j_end = (int)(HEIGHT / PIXELS_ON_UNIT - 2);
		}
		while (++map->i_start < map->i_end)
		{
			map->j_start = (j + 2) * PIXELS_ON_UNIT - PIXELS_ON_UNIT / 3 - 1;
			while (++map->j_start < map->j_end)
				my_mlx_pixel_put(&info->picture, map->i_start,
					map->j_start, 0x00995600);
		}
		inside3_draw_map_pixel(info, map, i, j);
	}
}

void	inside3_draw_map_pixel(t_info *info, t_map *map, int i, int j)
{
	if (i == 0 || info->map[j][i - 1] != '1')
	{
		map->i_start = (i + 1) * PIXELS_ON_UNIT - 1;
		map->i_end = map->i_start + 1 + PIXELS_ON_UNIT / 3;
		if (map->i_end + 1 > WIDTH)
			map->i_end = WIDTH - 1;
		map->j_start = (j + 1) * PIXELS_ON_UNIT;
		map->j_end = map->j_start + PIXELS_ON_UNIT;
		if (map->j_end + 1 > HEIGHT)
			map->j_end = (int)(HEIGHT / PIXELS_ON_UNIT - 2);
		if (i > 0 && j > 0 && ft_strlen(info->map[j - 1]) >= i + 1
			&& info->map[j - 1][i] == '1' && info->map[j - 1][i - 1] == '1')
			map->j_start = (j + 1) * PIXELS_ON_UNIT - PIXELS_ON_UNIT / 3;
	}
	while (++map->i_start < map->i_end)
	{
		map->j_start = (j + 1) * PIXELS_ON_UNIT - 1;
		if (i > 0 && j > 0 && ft_strlen(info->map[j - 1]) >= i + 1
			&& info->map[j - 1][i] == '1' && info->map[j - 1][i - 1] == '1')
			map->j_start = (j + 1) * PIXELS_ON_UNIT - PIXELS_ON_UNIT / 3 - 1;
		while (++map->j_start < map->j_end)
			my_mlx_pixel_put(&info->picture, map->i_start,
				map->j_start, 0x00995600);
	}
}
