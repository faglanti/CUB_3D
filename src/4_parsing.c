/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:17:07 by faglanti          #+#    #+#             */
/*   Updated: 2022/06/27 10:42:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	check_orient(t_info *info, char *str, int *orient, int i)
{
	if (orient[i] == 1)
		return (print_errors(info, 5, NULL));
	orient[i] = 1;
	if (save_parameters(info, str, i))
		return (1);
	i = 0;
	while (i < 6)
	{
		if (!orient[i++])
		{
			orient[6] = 0;
			break ;
		}
		orient[6] = 1;
	}
	return (0);
}

int	data_from_file(t_info *info, char *str, int *orient)
{
	int	i;

	i = 0;
	if (str[i] == 'N' && str[i + 1] == 'O' && str[i + 2] == ' ')
	{
		if (check_orient(info, str, orient, 0))
			return (1);
	}
	else if (str[i] == 'S' && str[i + 1] == 'O' && str[i + 2] == ' ')
	{
		if (check_orient(info, str, orient, 1))
			return (1);
	}
	else if (str[i] == 'W' && str[i + 1] == 'E' && str[i + 2] == ' ')
	{
		if (check_orient(info, str, orient, 2))
			return (1);
	}
	else
		if (inside_data_from_file(info, str, i, orient))
			return (1);
	return (0);
}

int	inside_data_from_file(t_info *info, char *str, int i, int *orient)
{
	if (str[i] == 'E' && str[i + 1] == 'A' && str[i + 2] == ' ')
	{
		if (check_orient(info, str, orient, 3))
			return (1);
	}
	else if (str[i] == 'F' && str[i + 1] == ' ')
	{
		if (check_orient(info, str, orient, 4))
			return (1);
	}
	else if (str[i] == 'C' && str[i + 1] == ' ')
	{
		if (check_orient(info, str, orient, 5))
			return (1);
	}
	else if (orient[6] != 1)
		return (print_errors(info, 6, NULL));
	else
	{
		if (reading_map(info, str))
			return (1);
	}
	return (0);
}

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
	if (is_valid_symbol(str, '0'))
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

int	is_valid_symbol(char *str, char flag)
{
	int	i;

	if (str)
	{
		i = -1;
		while (str[++i])
		{
			if (str[i] != 'N' && str[i] != 'S' && str[i] != 'E'
				&& str[i] != 'W' && str[i] != '1' && str[i] != '0'
				&& str[i] != ' ')
				return (1);
		}
	}
	if (!str)
	{
		if (flag != 'N' && flag != 'S' && flag != 'E'
			&& flag != 'W' && flag != '0')
			return (1);
	}
	return (0);
}
