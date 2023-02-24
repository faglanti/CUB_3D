/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_graphic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faglanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 10:20:11 by faglanti          #+#    #+#             */
/*   Updated: 2022/07/03 18:02:47 by faglanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	graphic(t_info *info)
{
	info->mlx = mlx_init();
	if (!info->mlx)
		return (print_errors(info, 7, "Can't init MLX library"));
	info->win = mlx_new_window(info->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!info->win)
		return (print_errors(info, 4, NULL));
	info->picture.image = mlx_new_image(info->mlx, WIDTH, HEIGHT);
	if (!info->picture.image)
		return (print_errors(info, 4, NULL));
	info->picture.addr = mlx_get_data_addr(info->picture.image,
			&info->picture.bits_per_pixel, &info->picture.line_length,
			&info->picture.endian);
	if (init_textures(info, info->no, &info->texture_no)
		|| init_textures(info, info->so, &info->texture_so)
		|| init_textures(info, info->we, &info->texture_we)
		|| init_textures(info, info->ea, &info->texture_ea))
		return (1);
	draw_image(info);
	return (0);
}

int	init_textures(t_info *info, char *file, t_img *texture)
{
	texture->image = mlx_xpm_file_to_image(info->mlx, file,
			&texture->width, &texture->height);
	if (!texture->image)
		return (print_errors(info, 4, NULL));
	texture->addr = mlx_get_data_addr(texture->image, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	return (0);
}

int	draw_image(t_info *info)
{
	t_draw	draw;
	int		i;

	i = -1;
	while (++i < WIDTH)
	{
		inside_draw_image(info, &draw, i);
		inside2_draw_image(info, &draw);
		inside3_draw_image(info, &draw);
		inside4_draw_image(info, &draw);
		inside5_draw_image(info, &draw, i);
		inside6_draw_image(info, &draw, i);
	}
	mlx_put_image_to_window(info->mlx, info->win, info->picture.image, 0, 0);
	return (0);
}

void	inside_draw_image(t_info *info, t_draw *draw, int i)
{
	draw->screen_to_camera = 2 * i / (double)(WIDTH) - 1;
	draw->ray_dir_x = info->init_dir_x + info->screen_x
		* draw->screen_to_camera;
	draw->ray_dir_y = info->init_dir_y + info->screen_y
		* draw->screen_to_camera;
	draw->map_player_x = (int)info->player_x;
	draw->map_player_y = (int)info->player_y;
	if (!draw->ray_dir_x)
		draw->delta_dist_x = 1e30;
	else
		draw->delta_dist_x = fabs(1 / draw->ray_dir_x);
	if (!draw->ray_dir_y)
		draw->delta_dist_y = 1e30;
	else
		draw->delta_dist_y = fabs(1 / draw->ray_dir_y);
}

void	inside2_draw_image(t_info *info, t_draw *draw)
{
	if (draw->ray_dir_x < 0)
	{
		draw->step_x = -1;
		draw->side_dist_x = (info->player_x - draw->map_player_x)
			* draw->delta_dist_x;
	}
	else
	{
		draw->step_x = 1;
		draw->side_dist_x = (draw->map_player_x + 1.0 - info->player_x)
			* draw->delta_dist_x;
	}
	if (draw->ray_dir_y < 0)
	{
		draw->step_y = -1;
		draw->side_dist_y = (info->player_y - draw->map_player_y)
			* draw->delta_dist_y;
	}
	else
	{
		draw->step_y = 1;
		draw->side_dist_y = (draw->map_player_y + 1.0 - info->player_y)
			* draw->delta_dist_y;
	}
}
