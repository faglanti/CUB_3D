/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faglanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:33:55 by faglanti          #+#    #+#             */
/*   Updated: 2022/07/03 18:03:44 by faglanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	parsing(t_info *info, int argc, char **argv)
{
	int	len;
	int	fd;

	if (argc == 2)
	{
		len = ft_strlen(argv[1]);
		if (len < 5)
			return (print_errors(info, 1, NULL));
		if (ft_strcmp(argv[1] + len - 4, ".cub"))
			return (print_errors(info, 1, NULL));
		fd = open(argv[1], O_DIRECTORY);
		if (fd > 0)
		{
			close(fd);
			return (print_errors(info, 3, argv[1]));
		}
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			return (print_errors(info, 4, NULL));
		if (reading_file(info, fd, get_next_line(fd), 0))
			return (1);
	}
	else
		return (print_errors(info, 2, NULL));
	return (0);
}

int	reading_file(t_info *info, int fd, char *str, int i)
{
	int		orient[7];

	while (i < 7)
		orient[i++] = 0;
	while (str)
	{
		if (!ft_strcmp(str, "") && !orient[6])
			free(str);
		else
			if (data_from_file(info, str, orient))
				return (1);
		str = get_next_line(fd);
	}
	if (errno == ENOMEM)
		return (print_errors(info, 4, NULL));
	close(fd);
	if (check_file_image(info) || check_player(info, info->list_map, 0, -1))
		return (1);
	info->map = (char **)malloc(sizeof(char *) * (info->map_height + 1));
	if (!info->map)
		return (print_errors(info, 4, NULL));
	info->map[info->map_height] = NULL;
	if (create_map_array(info, info->list_map, NULL, 0))
		return (1);
	return (0);
}

int	check_file_image(t_info *info)
{
	if (inside_check_file_image(info, info->no))
		return (1);
	if (inside_check_file_image(info, info->so))
		return (1);
	if (inside_check_file_image(info, info->we))
		return (1);
	if (inside_check_file_image(info, info->ea))
		return (1);
	return (0);
}

int	inside_check_file_image(t_info *info, char *str)
{
	int	len;
	int	fd;

	len = ft_strlen(str);
	if (len < 5 || ft_strcmp(str + len - 4, ".xpm"))
		return (print_errors(info, 7, "Not valid image file"));
	fd = open(str, O_DIRECTORY);
	if (fd > 0)
	{
		close(fd);
		return (print_errors(info, 7, "File image is a directory"));
	}
	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (print_errors(info, 4, NULL));
	close(fd);
	return (0);
}

int	check_player(t_info *info, t_list *temp, int k, int str_index)
{
	int		i;
	char	*str;
	char	player_char;

	while (temp)
	{
		i = -1;
		str = temp->content;
		++str_index;
		while (str[++i])
		{
			if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E'
				|| str[i] == 'W')
			{
				player_char = str[i];
				info->player_y = str_index + 0.5;
				info->player_x = i + 0.5;
				k++;
			}
		}
		temp = temp->next;
	}
	if (init_player_position(info, player_char, k))
		return (print_errors(info, 6, NULL));
	return (0);
}
