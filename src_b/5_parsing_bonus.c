/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_parsing_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faglanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:58:37 by faglanti          #+#    #+#             */
/*   Updated: 2022/08/01 14:36:28 by faglanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

int	reading_map(t_info *info, char *str)
{
	t_list	*list_tmp;

	if (!str || (!ft_strcmp(str, "") && !info->list_map))
	{
		free(str);
		return (0);
	}
	else if (!ft_strcmp(str, "") && info->list_map)
	{
		free(str);
		return (print_errors(info, 6, NULL));
	}
	if (is_valid_symbol(info, str))
	{
		free(str);
		return (print_errors(info, 6, NULL));
	}
	list_tmp = ft_lstnew(str);
	if (!list_tmp)
		return (print_errors(info, 4, NULL));
	ft_lstadd_back(&info->list_map, list_tmp);
	info->map_height++;
	return (0);
}

int	is_valid_symbol(t_info *info, char *str)
{
	int	i;

	if (str)
	{
		i = -1;
		while (str[++i])
		{
			if (str[i] != 'N' && str[i] != 'S' && str[i] != 'E'
				&& str[i] != 'W' && str[i] != '1' && str[i] != '0'
				&& str[i] != ' ' && str[i] != '2' && str[i] != '8')
				return (1);
			if (str[i] == '8')
			{
				info->count_sprites++;
				info->sprite_y = info->map_height + 0.5;
				info->sprite_x = i + 0.5;
				if (!info->list_sprite_images || info->count_sprites > 1)
					return (1);
			}
			if (str[i] == '2')
				info->count_doors++;
		}
	}
	return (0);
}

int	create_map_array(t_info *info, t_list *tmp, char *str, int j)
{
	int	i;

	while (tmp)
	{
		i = -1;
		str = (char *)tmp->content;
		while (str[++i])
			if (str[i] != ' ')
				break ;
		if (i == ft_strlen(str))
			return (print_errors(info, 6, NULL));
		i = ft_strlen(str);
		while (str[--i] == ' ')
			;
		if (i + 1 > info->map_width)
			info->map_width = i + 1;
		info->map[j] = ft_substr(str, 0, i + 1);
		if (!info->map[j++])
			return (print_errors(info, 4, NULL));
		tmp = tmp->next;
	}
	ft_lstdel(&info->list_map);
	if (is_map_valid(info))
		return (1);
	return (0);
}

int	is_map_valid(t_info *info)
{
	int	i;
	int	k;

	if (inside_is_map_valid(info, 0, 0, 0))
		return (1);
	i = -1;
	while (++i < info->map_width)
	{
		k = info->map_height - 1;
		while (i >= ft_strlen(info->map[k]) || info->map[k][i] == ' ')
			k--;
		if (inside2_is_map_valid(info, i, -1, k))
			return (1);
	}
	return (0);
}

int	inside_is_map_valid(t_info *info, int i, int j, int open)
{
	while (info->map[i])
	{
		j = 0;
		while (info->map[i][j])
		{
			if (info->map[i][j] == '1' && !open)
				open = 1;
			if (open && ((info->map[i][j] == ' ' && info->map[i][j - 1] == '1')
				|| (j == ft_strlen(info->map[i]) - 1
				&& info->map[i][j] == '1')))
				open = 0;
			if (open && info->map[i][j] == ' ')
				return (print_errors(info, 6, NULL));
			if ((info->map[i][j] == 'N' || info->map[i][j] == 'S'
				|| info->map[i][j] == 'W' || info->map[i][j] == 'E'
				|| info->map[i][j] == '0') && !open)
				return (print_errors(info, 6, NULL));
			j++;
		}
		if (open)
			return (print_errors(info, 6, NULL));
		i++;
	}
	return (0);
}
