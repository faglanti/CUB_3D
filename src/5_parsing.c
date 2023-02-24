/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:18:14 by faglanti          #+#    #+#             */
/*   Updated: 2022/06/26 09:33:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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

int	inside2_is_map_valid(t_info *info, int i, int j, int k)
{
	int	open;

	open = 0;
	while (++j < info->map_height)
	{
		if (i < ft_strlen(info->map[j]))
		{
			if (!open && info->map[j][i] == '1')
				open = 1;
			if (open && ((info->map[j][i] == ' ' && info->map[j - 1][i] == '1')
				|| (j == k && info->map[j][i] == '1')))
				open = 0;
			if (open && info->map[j][i] == ' ' )
				return (print_errors(info, 6, NULL));
			if ((info->map[j][i] == 'N' || info->map[j][i] == 'S'
			|| info->map[j][i] == 'W' || info->map[j][i] == 'E'
			|| info->map[j][i] == '0') && !open)
				return (print_errors(info, 6, NULL));
		}
	}
	if (open)
		return (print_errors(info, 6, NULL));
	return (0);
}
