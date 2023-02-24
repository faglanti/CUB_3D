/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:16:03 by faglanti          #+#    #+#             */
/*   Updated: 2022/06/26 09:33:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	init_player_position(t_info *info, char player_char, int k)
{
	if (k != 1)
		return (1);
	if (player_char == 'W')
	{
		info->init_dir_x = -1;
		info->screen_y = -1;
	}
	else if (player_char == 'S')
	{
		info->init_dir_y = 1;
		info->screen_x = -1;
	}
	else if (player_char == 'E')
	{
		info->init_dir_x = 1;
		info->screen_y = 1;
	}
	else if (player_char == 'N')
	{
		info->init_dir_y = -1;
		info->screen_x = 1;
	}
	return (0);
}

int	save_parameters(t_info *info, char *str, int i)
{
	int	k;

	if (i < 4)
	{
		if (inside_save_param(info, str, i))
			return (1);
	}
	else if (i > 3)
	{
		k = 1;
		while (str[k] == ' ')
			k++;
		if (i == 4 || i == 5)
		{
			if (get_color_param(info, &str[k], i))
			{
				free(str);
				return (1);
			}
			free(str);
		}
	}
	return (0);
}

int	inside_save_param(t_info *info, char *str, int i)
{
	char	*tmp;
	int		k;
	int		j;

	k = 2;
	while (str[k] == ' ')
		k++;
	j = ft_strlen(str);
	while (str[j] == ' ' || !str[j])
		j--;
	tmp = ft_substr(str, k, j - k + 1);
	free(str);
	if (!tmp)
		return (print_errors(info, 4, NULL));
	if (i == 0)
		info->no = tmp;
	else if (i == 1)
		info->so = tmp;
	else if (i == 2)
		info->we = tmp;
	else if (i == 3)
		info->ea = tmp;
	return (0);
}

int	get_color_param(t_info *info, char *str, int param)
{
	int	i;
	int	color[3];

	i = 0;
	while (i < 3)
		color[i++] = -1;
	if (inside_ger_color_param(info, str, color, 0))
		return (1);
	i = -1;
	while (++i < 3)
		if (color[i] == -1)
			return (print_errors(info, 6, NULL));
	if (param == 4)
		info->floor_color = 0 << 24 | color[0] << 16 | color[1] << 8 | color[2];
	else if (param == 5)
		info->ceiling_color = 0 << 24 | color[0] << 16
			| color[1] << 8 | color[2];
	return (0);
}

int	inside_ger_color_param(t_info *info, char *str, int *color, int k)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			color[k] = 0;
			while (str[i] >= '0' && str[i] <= '9')
				color[k] = color[k] * 10 + str[i++] - 48;
			if (color[k] > 255)
				return (print_errors(info, 6, NULL));
			if (!str[i] || str[i] == ' ')
				break ;
			k++;
			if (str[i] != ',' || k > 2)
				return (print_errors(info, 6, NULL));
			while (str[++i] == ' ')
				;
		}
		else
			return (print_errors(info, 6, NULL));
	}
	return (0);
}
