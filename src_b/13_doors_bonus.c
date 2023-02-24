/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_doors_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faglanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:26:08 by faglanti          #+#    #+#             */
/*   Updated: 2022/08/01 13:27:42 by faglanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	create_door_arr(t_info *info)
{
	int	j;
	int	i;
	int	len;
	int	door;

	j = -1;
	door = 0;
	while (++j < info->map_height)
	{
		i = -1;
		len = ft_strlen(info->map[j]);
		while (++i < len)
		{
			if (info->map[j][i] == '2')
			{
				info->door_arr[door].door_x = i;
				info->door_arr[door].door_y = j;
				info->door_arr[door].cur_delta = 0;
				info->door_arr[door].status = 2;
				door++;
			}
		}
	}
}

void	change_status_doors(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->count_doors)
	{
		if (info->door_arr[i].status == 3)
		{
			info->door_arr[i].cur_delta += SPEED_DOOR;
			if (info->door_arr[i].cur_delta >= 1)
			{
				info->door_arr[i].status = 4;
				info->door_arr[i].cur_delta = 0;
			}
		}
		else if (info->door_arr[i].status == 6)
		{
			info->door_arr[i].cur_delta += SPEED_DOOR;
			if (info->door_arr[i].cur_delta >= 1)
			{
				info->door_arr[i].status = 2;
				info->door_arr[i].cur_delta = 0;
			}
		}
	}
}

void	door_on_map(t_info *info, t_draw *draw, int d)
{
	if (info->map[draw->map_player_y][draw->map_player_x] == '2')
	{
		d = find_door_in_array(info, draw->map_player_y, draw->map_player_x);
		if (info->door_arr[d].status == 2)
			draw->hit = 2;
		else if (info->door_arr[d].status == 3 || info->door_arr[d].status == 6)
		{
			ft_intjoin(info, draw, d);
			info->door_arr[d].side_door = draw->side;
			if (info->door_arr[d].side_door == 0)
				info->door_arr[d].door_dist = draw->side_dist_x
					- draw->delta_dist_x;
			else
				info->door_arr[d].door_dist
					= draw->side_dist_y - draw->delta_dist_y;
		}
	}
	else if (info->map[draw->map_player_y][draw->map_player_x] == '8')
	{
		if (draw->side == 0)
			draw->sprite_dist = draw->side_dist_x - draw->delta_dist_x;
		else
			draw->sprite_dist = draw->side_dist_y - draw->delta_dist_y;
		ft_intjoin(info, draw, info->count_doors);
	}
}

int	find_door_in_array(t_info *info, int y, int x)
{
	int	i;

	i = -1;
	while (++i < info->count_doors)
	{
		if (info->door_arr[i].door_y == y && info->door_arr[i].door_x == x)
			return (i);
	}
	return (-1);
}

void	draw_opening_door(t_info *info, t_draw *draw, int i, int door_index)
{
	draw->line_height = (int)(HEIGHT / info->door_arr[door_index].door_dist);
	draw->draw_end = (draw->line_height + HEIGHT) / 2;
	draw->draw_start = (int)(draw->draw_end - draw->line_height
			* (1 - info->door_arr[door_index].cur_delta));
	if (info->door_arr[door_index].side_door == 0)
		draw->wall_x = info->player_y + info->door_arr[door_index].door_dist
			* draw->ray_dir_y;
	else
		draw->wall_x = info->player_x + info->door_arr[door_index].door_dist
			* draw->ray_dir_x;
	draw->wall_x -= floor(draw->wall_x);
	draw->tmp_texture = &info->texture_door;
	draw->tex_x = (int)(draw->wall_x * (double)(draw->tmp_texture->width));
	if (info->door_arr[door_index].side_door == 0 && draw->ray_dir_x > 0)
		draw->tex_x = draw->tmp_texture->width - draw->tex_x - 1;
	if (info->door_arr[door_index].side_door == 1 && draw->ray_dir_y < 0)
		draw->tex_x = draw->tmp_texture->width - draw->tex_x - 1;
	draw->step = 1.0 * draw->tmp_texture->height / draw->line_height;
	inside_draw_opening_door(info, draw, i, door_index);
}
