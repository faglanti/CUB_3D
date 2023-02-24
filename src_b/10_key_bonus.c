/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_key_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faglanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:20:32 by faglanti          #+#    #+#             */
/*   Updated: 2022/08/01 13:21:16 by faglanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

int	key_hook(int keycode, t_info *info)
{
	if (keycode == 53)
		quit(info);
	if (info->map[(int)info->player_y][(int)info->player_x] == '2'
		&& info->door_arr[find_door_in_array(info, (int)info->player_y,
		(int)info->player_x)].status == 4)
			info->door_arr[find_door_in_array(info, (int)info->player_y,
				(int)info->player_x)].status = 5;
	if (keycode == 13 || keycode == 1)
		up_down(info, keycode, 0);
	if (keycode == 0 || keycode == 2)
		left_right(info, keycode, 0);
	if (keycode == 123 || keycode == 124)
		rotate_left_right(info, keycode, info->screen_x, info->init_dir_x);
	if (keycode == 46)
	{
		if (info->map_activity)
			info->map_activity = 0;
		else
			info->map_activity = 1;
	}
	if (keycode == 49)
		space_pressed(info, (int)info->player_x, (int)info->player_y, 0);
	return (0);
}

void	space_pressed(t_info *info, int x, int y, int i)
{
	if (info->map[y + 1][x] == '2')
	{
		i = find_door_in_array(info, y + 1, x);
		if (i > -1 && info->door_arr[i].status == 2)
			info->door_arr[i].status = 3;
	}
	if (info->map[y - 1][x] == '2')
	{
		i = find_door_in_array(info, y - 1, x);
		if (i > -1 && info->door_arr[i].status == 2)
			info->door_arr[i].status = 3;
	}
	if (info->map[y][x + 1] == '2')
	{
		i = find_door_in_array(info, y, x + 1);
		if (i > -1 && info->door_arr[i].status == 2)
			info->door_arr[i].status = 3;
	}
	if (info->map[y][x - 1] == '2')
	{
		i = find_door_in_array(info, y, x - 1);
		if (i > -1 && info->door_arr[i].status == 2)
			info->door_arr[i].status = 3;
	}
}

void	up_down(t_info *info, int keycode, int i)
{
	if (keycode == 13)
	{
		define_indent_sign(info->init_dir_x, &i);
		if (!check_sym_for_move(info, (int)info->player_y, (int)(info->player_x
				+ info->init_dir_x * MOVE_SPEED + i * INDENT)))
			info->player_x += info->init_dir_x * MOVE_SPEED;
		define_indent_sign(info->init_dir_y, &i);
		if (!check_sym_for_move(info, (int)(info->player_y + info->init_dir_y
				* MOVE_SPEED + i * INDENT), (int)info->player_x))
			info->player_y += info->init_dir_y * MOVE_SPEED;
		return ;
	}
	define_indent_sign(-info->init_dir_x, &i);
	if (!check_sym_for_move(info, (int)info->player_y,
			(int)(info->player_x - info->init_dir_x * MOVE_SPEED + i * INDENT)))
		info->player_x -= info->init_dir_x * MOVE_SPEED;
	define_indent_sign(-info->init_dir_y, &i);
	if (!check_sym_for_move(info, (int)(info->player_y - info->init_dir_y
			* MOVE_SPEED + i * INDENT), (int)info->player_x))
		info->player_y -= info->init_dir_y * MOVE_SPEED;
}

int	check_sym_for_move(t_info *info, int y, int x)
{
	char	c;
	int		i;

	c = info->map[y][x];
	if (c == '2')
	{
		i = find_door_in_array(info, y, x);
		if (info->door_arr[i].status != 4 && info->door_arr[i].status != 5)
			return (1);
	}
	else if (c != 'N' && c != 'S' && c != 'E'
		&& c != 'W' && c != '0')
		return (1);
	return (0);
}

void	left_right(t_info *info, int keycode, int i)
{
	if (keycode == 0)
	{
		define_indent_sign(-info->screen_x, &i);
		if (!check_sym_for_move(info, (int)info->player_y, (int)(info->player_x
				- info->screen_x * MOVE_SPEED + i * INDENT)))
			info->player_x -= info->screen_x * MOVE_SPEED;
		define_indent_sign(-info->screen_y, &i);
		if (!check_sym_for_move(info, (int)(info->player_y - info->screen_y
				* MOVE_SPEED + i * INDENT), (int)info->player_x))
			info->player_y -= info->screen_y * MOVE_SPEED;
		return ;
	}
	define_indent_sign(info->screen_x, &i);
	if (!check_sym_for_move(info, (int)info->player_y, (int)(info->player_x
			+ info->screen_x * MOVE_SPEED + i * INDENT)))
		info->player_x += info->screen_x * MOVE_SPEED;
	define_indent_sign(info->screen_y, &i);
	if (!check_sym_for_move(info, (int)(info->player_y + info->screen_y
			* MOVE_SPEED + i * INDENT), (int)info->player_x))
		info->player_y += info->screen_y * MOVE_SPEED;
}
