/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_parsing_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faglanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:00:01 by faglanti          #+#    #+#             */
/*   Updated: 2022/08/01 11:00:24 by faglanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

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
