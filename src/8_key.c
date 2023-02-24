/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_key.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faglanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 18:14:12 by faglanti          #+#    #+#             */
/*   Updated: 2022/07/03 18:02:17 by faglanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	define_indent_sign(double num, int *i)
{
	if (num < 0)
		*i = -1;
	else
		*i = 1;
}

int	key_hook(int keycode, t_info *info)
{
	if (keycode == 53)
		quit(info);
	if (keycode == 13 || keycode == 1)
		up_down(info, keycode, 0);
	if (keycode == 0 || keycode == 2)
		left_right(info, keycode, 0);
	if (keycode == 123 || keycode == 124)
		rotate_left_right(info, keycode, info->screen_x, info->init_dir_x);
	return (0);
}

void	up_down(t_info *info, int keycode, int i)
{
	if (keycode == 13)
	{
		define_indent_sign(info->init_dir_x, &i);
		if (!is_valid_symbol(NULL, info->map[(int)info->player_y]
				[(int)(info->player_x + info->init_dir_x
					* MOVE_SPEED + i * INDENT)]))
			info->player_x += info->init_dir_x * MOVE_SPEED;
		define_indent_sign(info->init_dir_y, &i);
		if (!is_valid_symbol(NULL, info->map[(int)(info->player_y
					+ info->init_dir_y * MOVE_SPEED + i
					* INDENT)][(int)info->player_x]))
			info->player_y += info->init_dir_y * MOVE_SPEED;
		return ;
	}
	define_indent_sign(info->init_dir_x, &i);
	if (!is_valid_symbol(NULL, info->map[(int)info->player_y]
			[(int)(info->player_x - info->init_dir_x
				* MOVE_SPEED + i * INDENT)]))
		info->player_x -= info->init_dir_x * MOVE_SPEED;
	define_indent_sign(info->init_dir_y, &i);
	if (!is_valid_symbol(NULL, info->map[(int)(info->player_y
				- info->init_dir_y * MOVE_SPEED + i
				* INDENT)][(int)info->player_x]))
		info->player_y -= info->init_dir_y * MOVE_SPEED;
}

void	left_right(t_info *info, int keycode, int i)
{
	if (keycode == 0)
	{
		define_indent_sign(-info->screen_x, &i);
		if (!is_valid_symbol(NULL, info->map[(int)info->player_y]
				[(int)(info->player_x - info->screen_x
					* MOVE_SPEED + i * INDENT)]))
			info->player_x -= info->screen_x * MOVE_SPEED;
		define_indent_sign(-info->screen_y, &i);
		if (!is_valid_symbol(NULL, info->map[(int)(info->player_y
					- info->screen_y * MOVE_SPEED + i
					* INDENT)][(int)info->player_x]))
			info->player_y -= info->screen_y * MOVE_SPEED;
		return ;
	}
	define_indent_sign(info->screen_x, &i);
	if (!is_valid_symbol(NULL, info->map[(int)info->player_y]
			[(int)(info->player_x + info->screen_x
				* MOVE_SPEED + i * INDENT)]))
		info->player_x += info->screen_x * MOVE_SPEED;
	define_indent_sign(info->screen_y, &i);
	if (!is_valid_symbol(NULL, info->map[(int)(info->player_y
				+ info->screen_y * MOVE_SPEED + i
				* INDENT)][(int)info->player_x]))
		info->player_y += info->screen_y * MOVE_SPEED;
}

void	rotate_left_right(t_info *info, int keycode,
	double old_screen_x, double old_dir_x)
{
	if (keycode == 124)
	{
		info->init_dir_x = info->init_dir_x * cos(ROT_SPEED) - info->init_dir_y
			* sin(ROT_SPEED);
		info->init_dir_y = old_dir_x * sin(ROT_SPEED) + info->init_dir_y
			* cos(ROT_SPEED);
		info->screen_x = info->screen_x * cos(ROT_SPEED) - info->screen_y
			* sin(ROT_SPEED);
		info->screen_y = old_screen_x * sin(ROT_SPEED) + info->screen_y
			* cos(ROT_SPEED);
	}
	if (keycode == 123)
	{
		info->init_dir_x = info->init_dir_x * cos(-ROT_SPEED) - info->init_dir_y
			* sin(-ROT_SPEED);
		info->init_dir_y = old_dir_x * sin(-ROT_SPEED) + info->init_dir_y
			* cos(-ROT_SPEED);
		info->screen_x = info->screen_x * cos(-ROT_SPEED) - info->screen_y
			* sin(-ROT_SPEED);
		info->screen_y = old_screen_x * sin(-ROT_SPEED) + info->screen_y
			* cos(-ROT_SPEED);
	}
}
