/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_mouse_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faglanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:29:11 by faglanti          #+#    #+#             */
/*   Updated: 2022/08/01 13:29:33 by faglanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

int	for_mouse_up(int button, int x, int y, t_info *info)
{
	if (button == 2)
	{
		mlx_mouse_show(info->mlx, info->win);
		info->mouse_press = 0;
	}
	(void)x;
	(void)y;
	return (0);
}

int	for_mouse_down(int button, int x, int y, t_info *info)
{
	if (button == 2)
	{
		mlx_mouse_hide(info->mlx, info->win);
		info->mouse_press = 1;
	}
	(void)x;
	(void)y;
	return (0);
}

int	rot_view(t_info *info)
{
	int		x;
	int		y;
	double	rot_speed;
	double	old_screen_x;
	double	old_dir_x;

	old_screen_x = info->screen_x;
	old_dir_x = info->init_dir_x;
	mlx_mouse_get_pos(info->win, &x, &y);
	rot_speed = (x - WIDTH / 2.0) / 1500;
	if (x > (WIDTH + 100) / 2)
		inside_rot_view(info, rot_speed, old_dir_x, old_screen_x);
	else if (x < (WIDTH - 100) / 2)
	{
		info->init_dir_x = info->init_dir_x * cos(rot_speed) - info->init_dir_y
			* sin(rot_speed);
		info->init_dir_y = old_dir_x * sin(rot_speed) + info->init_dir_y
			* cos(rot_speed);
		info->screen_x = info->screen_x * cos(rot_speed) - info->screen_y
			* sin(rot_speed);
		info->screen_y = old_screen_x * sin(rot_speed) + info->screen_y
			* cos(rot_speed);
		mlx_mouse_move(info->win, WIDTH / 2, HEIGHT / 2);
	}
	return (0);
}

void	inside_rot_view(t_info *info, double rot_speed, double old_dir_x,
	double old_screen_x)
{
	info->init_dir_x = info->init_dir_x * cos(rot_speed) - info->init_dir_y
		* sin(rot_speed);
	info->init_dir_y = old_dir_x * sin(rot_speed) + info->init_dir_y
		* cos(rot_speed);
	info->screen_x = info->screen_x * cos(rot_speed) - info->screen_y
		* sin(rot_speed);
	info->screen_y = old_screen_x * sin(rot_speed) + info->screen_y
		* cos(rot_speed);
	mlx_mouse_move(info->win, WIDTH / 2, HEIGHT / 2);
}
