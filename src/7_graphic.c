/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_graphic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:20:43 by faglanti          #+#    #+#             */
/*   Updated: 2022/06/26 09:33:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	inside3_draw_image(t_info *info, t_draw *draw)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (draw->side_dist_x < draw->side_dist_y)
		{
			draw->side_dist_x += draw->delta_dist_x;
			draw->map_player_x += draw->step_x;
			draw->side = 0;
		}
		else
		{
			draw->side_dist_y += draw->delta_dist_y;
			draw->map_player_y += draw->step_y;
			draw->side = 1;
		}
		if (info->map[draw->map_player_y][draw->map_player_x] == '1')
			hit = 1;
	}
	if (draw->side == 0)
		draw->wall_dist = draw->side_dist_x - draw->delta_dist_x;
	else
		draw->wall_dist = draw->side_dist_y - draw->delta_dist_y;
}

void	inside4_draw_image(t_info *info, t_draw *draw)
{
	draw->line_height = (int)(HEIGHT / draw->wall_dist * HEIGHT / WIDTH);
	draw->draw_start = HEIGHT / 2 - draw->line_height / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = draw->line_height / 2 + HEIGHT / 2;
	if (draw->draw_end > HEIGHT)
		draw->draw_end = HEIGHT;
	if (draw->side == 0)
		draw->wall_x = info->player_y + draw->wall_dist * draw->ray_dir_y;
	else
		draw->wall_x = info->player_x + draw->wall_dist * draw->ray_dir_x;
	draw->wall_x -= floor(draw->wall_x);
	if (draw->side == 0 && draw->ray_dir_x > 0)
		draw->tmp_texture = &info->texture_we;
	else if (draw->side == 0 && draw->ray_dir_x <= 0)
		draw->tmp_texture = &info->texture_ea;
	else if (draw->side == 1 && draw->ray_dir_y > 0)
		draw->tmp_texture = &info->texture_so;
	else if (draw->side == 1 && draw->ray_dir_y <= 0)
		draw->tmp_texture = &info->texture_no;
}

void	inside5_draw_image(t_info *info, t_draw *draw, int i)
{
	int	j;

	draw->tex_x = (int)(draw->wall_x * (double)(draw->tmp_texture->width));
	if (draw->side == 0 && draw->ray_dir_x > 0)
		draw->tex_x = draw->tmp_texture->width - draw->tex_x - 1;
	if (draw->side == 1 && draw->ray_dir_y < 0)
		draw->tex_x = draw->tmp_texture->width - draw->tex_x - 1;
	j = 0;
	while (j < draw->draw_start)
	{
		my_mlx_pixel_put(&info->picture, i, j, info->ceiling_color);
		j++;
	}
	draw->step = 1.0 * draw->tmp_texture->height / draw->line_height;
	draw->tex_pos = (draw->draw_start - HEIGHT / 2
			+ draw->line_height / 2) * draw->step;
}

void	inside6_draw_image(t_info *info, t_draw *draw, int i)
{
	unsigned int	color;

	while (draw->draw_start <= draw->draw_end)
	{
		draw->tex_y = (int)draw->tex_pos & (draw->tmp_texture->height - 1);
		draw->tex_pos += draw->step;
		color = *(unsigned int *)((char *)draw->tmp_texture->addr + draw->tex_x
				* draw->tmp_texture->line_length + draw->tex_y
				* draw->tmp_texture->bits_per_pixel / 8);
		if (draw->side == 1)
			color = (color >> 1) & 8355711;
		my_mlx_pixel_put(&info->picture, i, draw->draw_start, color);
		draw->draw_start++;
	}
	while (draw->draw_end < HEIGHT)
	{
		my_mlx_pixel_put(&info->picture, i, draw->draw_end, info->floor_color);
		draw->draw_end++;
	}
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
