/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_graphic_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faglanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:18:33 by faglanti          #+#    #+#             */
/*   Updated: 2022/08/01 13:19:54 by faglanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

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
	drawing_doors_sprites(info, draw, i);
	free(draw->objects);
}

void	drawing_doors_sprites(t_info *info, t_draw *draw, int i)
{
	int	k;

	if (draw->objects)
	{
		k = draw->count_objects - 1;
		while (k >= 0)
		{
			if (draw->objects[k] == info->count_doors)
			{
				inside_draw_sprite(info);
				draw_sprite(info, draw, i, 0);
			}
			else
			{
				if (info->door_arr[draw->objects[k]].status == 3)
					draw_opening_door(info, draw, i, draw->objects[k]);
				else
					draw_closing_door(info, draw, i, draw->objects[k]);
			}
			k--;
		}
	}
}

void	draw_sprite(t_info *info, t_draw *draw, int i, int y)
{
	int	d;

	if (i >= info->sp.draw_start_x && i < info->sp.draw_end_x)
	{
		info->sp.tex_x = (int)(256 * (i - (-info->sp.width / 2
						+ info->sp.screen_x)) * info->sp.texture->width
				/ info->sp.width) / 256;
		if (info->sp.transform_y > 0 && i > 0 && i < WIDTH
			&& info->sp.transform_y < draw->wall_dist)
		{
			y = info->sp.draw_start_y - 1;
			while (++y < info->sp.draw_end_y)
			{
				d = y * 256 - HEIGHT * 128 + info->sp.height * 128;
				info->sp.tex_y = ((d * info->sp.texture->height)
						/ info->sp.height) / 256;
				info->sp.color = *(unsigned int *)((char *)
						info->sp.texture->addr + info->sp.tex_y
						* info->sp.texture->line_length + info->sp.tex_x
						* info->sp.texture->bits_per_pixel / 8);
				if ((info->sp.color & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(&info->picture, i, y, info->sp.color);
			}
		}
	}
}

void	inside_draw_sprite(t_info *info)
{
	info->sp.sprite_x = info->sprite_x - info->player_x;
	info->sp.sprite_y = info->sprite_y - info->player_y;
	info->sp.invdet = 1.0 / (info->screen_x * info->init_dir_y
			- info->init_dir_x * info->screen_y);
	info->sp.transform_x = info->sp.invdet * (info->init_dir_y
			* info->sp.sprite_x - info->init_dir_x * info->sp.sprite_y);
	info->sp.transform_y = info->sp.invdet * (-info->screen_y
			* info->sp.sprite_x + info->screen_x * info->sp.sprite_y);
	info->sp.screen_x = (int)((WIDTH / 2)
			* (1 + info->sp.transform_x / info->sp.transform_y));
	info->sp.height = abs((int)(HEIGHT / info->sp.transform_y));
	info->sp.draw_start_y = -info->sp.height / 2 + HEIGHT / 2;
	if (info->sp.draw_start_y < 0)
		info->sp.draw_start_y = 0;
	info->sp.draw_end_y = info->sp.height / 2 + HEIGHT / 2;
	if (info->sp.draw_end_y >= HEIGHT)
		info->sp.draw_end_y = HEIGHT - 1;
	info->sp.width = abs((int)(HEIGHT / info->sp.transform_y));
	info->sp.draw_start_x = -info->sp.width / 2 + info->sp.screen_x;
	if (info->sp.draw_start_x < 0)
		info->sp.draw_start_x = 0;
	info->sp.draw_end_x = info->sp.width / 2 + info->sp.screen_x;
	if (info->sp.draw_end_x >= WIDTH)
		info->sp.draw_end_x = WIDTH - 1;
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x
				* (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}
