/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faglanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:06:20 by faglanti          #+#    #+#             */
/*   Updated: 2022/06/24 15:06:20 by faglanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	main(int argc, char **argv)
{
	t_info	info;

	init(&info);
	if (parsing(&info, argc, argv))
		return (1);
	if (graphic(&info))
		return (1);
	mlx_hook(info.win, 17, 1L << 5, quit, &info);
	mlx_loop_hook(info.mlx, draw_image, &info);
	mlx_hook(info.win, 02, 1L << 0, key_hook, &info);
	// mlx_key_hook(info.win, key_hook, &info);
	mlx_loop(info.mlx);
	return (0);
}

int	print_errors(t_info *info, int err, char *str)
{
	printf("Error\n");
	if (err == 1)
		printf("Invalid map name\n");
	else if (err == 2)
		printf("Invalid number of parameters\n");
	else if (err == 3)
		printf("%s is a directory\n", str);
	else if (err == 4)
		perror(NULL);
	else if (err == 5)
		printf("Duplicated parameters are in the file\n");
	else if (err == 6)
		printf("Invalid parameters in the file\n");
	else if (err == 7)
		printf("%s\n", str);
	free_all(info);
	return (1);
}
