/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faglanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:28:35 by faglanti          #+#    #+#             */
/*   Updated: 2022/08/01 14:35:00 by faglanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include "../get_next_line/get_next_line.h"
# include "../minilibx/mlx.h"

# define WIDTH 720
# define HEIGHT 480
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.05
# define INDENT 0.2

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_img
{
	void	*image;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct s_draw
{
	double	screen_to_camera;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_player_x;
	int		map_player_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	t_img	*tmp_texture;
}				t_draw;

typedef struct info
{
	void			*mlx;
	void			*win;
	t_img			picture;
	t_img			texture_no;
	t_img			texture_so;
	t_img			texture_ea;
	t_img			texture_we;
	t_list			*list_map;
	double			player_x;
	double			player_y;
	double			init_dir_x;
	double			init_dir_y;
	double			screen_x;
	double			screen_y;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	int				map_height;
	int				map_width;
	char			**map;
}				t_info;

//init.c
void	init(t_info *info);
void	free_all(t_info *info);
int		quit(t_info *info);

//parsing.c
int		parsing(t_info *info, int argc, char **argv);
int		print_errors(t_info *info, int err, char *str);
int		reading_file(t_info *info, int fd, char *str, int i);
int		check_file_image(t_info *info);
int		inside_check_file_image(t_info *info, char *str);
void	save_extention(t_info *info, int flag, int extention);
int		check_player(t_info *info, t_list *temp, int k, int str_index);
int		init_player_position(t_info *info, char player_char, int k);
int		save_parameters(t_info *info, char *str, int i);
int		inside_save_param(t_info *info, char *str, int i);
int		get_color_param(t_info *info, char *str, int param);
int		inside_ger_color_param(t_info *info, char *str, int *color, int k);
int		check_orient(t_info *info, char *str, int *orient, int i);
int		data_from_file(t_info *info, char *str, int *orient);
int		inside_data_from_file(t_info *info, char *str, int i, int *orient);
int		reading_map(t_info *info, char *str);
int		is_valid_symbol(char *str, char flag);
int		create_map_array(t_info *info, t_list *tmp, char *str, int j);
int		is_map_valid(t_info *info);
int		inside_is_map_valid(t_info *info, int i, int j, int open);
int		inside2_is_map_valid(t_info *info, int i, int j, int k);

//str.c
int		ft_strcmp(const char *s1, const char *s2);

//list.c
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **begin, t_list *new);
void	ft_lstdelone(t_list *list, void (*del)(void *));
void	ft_lstclear(t_list **begin, void (*del)(void *));
void	ft_lstdel(t_list **begin);

//graphic.c
int		graphic(t_info *info);
int		init_textures(t_info *info, char *file, t_img *texture);
int		draw_image(t_info *info);
void	inside_draw_image(t_info *info, t_draw *draw, int i);
void	inside2_draw_image(t_info *info, t_draw *draw);
void	inside3_draw_image(t_info *info, t_draw *draw);
void	inside4_draw_image(t_info *info, t_draw *draw);
void	inside5_draw_image(t_info *info, t_draw *draw, int i);
void	inside6_draw_image(t_info *info, t_draw *draw, int i);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
int		resize_window(t_info *info);

//key.c
void	define_indent_sign(double num, int *i);
int		key_hook(int keycode, t_info *info);
void	up_down(t_info *info, int keycode, int i);
void	left_right(t_info *info, int keycode, int i);
void	rotate_left_right(t_info *info, int keycode,
			double old_screen_x, double old_dir_x);

#endif