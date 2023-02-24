/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faglanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:28:35 by faglanti          #+#    #+#             */
/*   Updated: 2022/07/03 18:20:26 by faglanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

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
# define PIXELS_ON_UNIT 9
# define SPEED_DOOR 0.005

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

typedef struct s_map
{
	int	i_start;
	int	i_end;
	int	j_start;
	int	j_end;
	int	color;
	int	flag;
}			t_map;

typedef struct s_door
{
	int		door_x;
	int		door_y;
	int		status;
	double	cur_delta;
	double	door_dist;
	int		side_door;
}				t_door;

typedef struct sprite
{
	double			invdet;
	double			sprite_y;
	double			sprite_x;
	t_img			*texture;
	double			transform_x;
	double			transform_y;
	int				screen_x;
	int				height;
	int				draw_start_y;
	int				draw_end_y;
	int				width;
	int				draw_start_x;
	int				draw_end_x;
	int				tex_x;
	int				tex_y;
	unsigned int	color;
}	t_sprite;

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
	double	door_dist;
	int		door_x;
	int		door_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		side_door;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	t_img	*tmp_texture;
	int		*objects;
	int		count_objects;
	double	sprite_dist;
}			t_draw;

typedef struct info
{
	void			*mlx;
	void			*win;
	t_img			picture;
	t_img			texture_no;
	t_img			texture_so;
	t_img			texture_ea;
	t_img			texture_we;
	t_img			texture_door;
	t_img			*sprite_textures;
	t_list			*list_sprite_images;
	t_door			*door_arr;
	t_list			*list_map;
	t_sprite		sp;
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
	char			*door;
	int				count_doors;
	int				count_sprite_images;
	int				count_sprites;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	int				map_height;
	int				map_width;
	char			**map;
	int				map_activity;
	int				mouse_press;
	double			sprite_x;
	double			sprite_y;
	int				timer;
}				t_info;

//init.c
void	init(t_info *info);
void	inside_init(t_info *info);
void	free_all(t_info *info);
void	inside_free_all(t_info *info);
int		quit(t_info *info);

//parsing.c
int		parsing(t_info *info, int argc, char **argv);
int		print_errors(t_info *info, int err, char *str);
int		reading_file(t_info *info, int fd, char *str, int i);
int		inside_reading_file(t_info *info);
void	create_door_arr(t_info *info);
int		check_file_image(t_info *info);
int		inside_check_file_image(t_info *info, char *str);
void	save_extention(t_info *info, int flag, int extention);
int		check_player(t_info *info, t_list *temp, int k, int str_index);
int		init_player_position(t_info *info, char player_char, int k);
int		save_parameters(t_info *info, char *str, int i);
int		inside_save_param(t_info *info, char *str, int i, int k);
int		make_list_sprite_images(t_info *info, char *str);
int		get_color_param(t_info *info, char *str, int param);
int		inside_ger_color_param(t_info *info, char *str, int *color, int k);
int		check_orient(t_info *info, char *str, int *orient, int i);
int		data_from_file(t_info *info, char *str, int *orient);
int		inside_data_from_file(t_info *info, char *str, int i, int *orient);
int		reading_map(t_info *info, char *str);
int		is_valid_symbol(t_info *info, char *str);
int		create_map_array(t_info *info, t_list *tmp, char *str, int j);
int		is_map_valid(t_info *info);
int		inside_is_map_valid(t_info *info, int i, int j, int open);
int		inside2_is_map_valid(t_info *info, int i, int j, int k);

//str.c
int		ft_strcmp(const char *s1, const char *s2);
void	ft_intjoin(t_info *info, t_draw *draw, int num);

//list.c
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **begin, t_list *new);
void	ft_lstdelone(t_list *list, void (*del)(void *));
void	ft_lstclear(t_list **begin, void (*del)(void *));
void	ft_lstdel(t_list **begin);

//graphic.c
int		graphic(t_info *info);
int		inside_graphic(t_info *info);
int		init_textures(t_info *info, char *file, t_img *texture);
int		draw_image(t_info *info);
void	change_status_doors(t_info *info);
void	change_sprite_textures(t_info *info);
void	inside_draw_image(t_info *info, t_draw *draw, int i);
void	inside2_draw_image(t_info *info, t_draw *draw);
void	inside3_draw_image(t_info *info, t_draw *draw);
void	door_on_map(t_info *info, t_draw *draw, int d);
int		find_door_in_array(t_info *info, int y, int x);
void	inside4_draw_image(t_info *info, t_draw *draw);
void	inside5_draw_image(t_info *info, t_draw *draw, int i);
void	inside6_draw_image(t_info *info, t_draw *draw, int i);
void	drawing_doors_sprites(t_info *info, t_draw *draw, int i);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
int		resize_window(t_info *info);

//key.c
int		key_hook(int keycode, t_info *info);
int		check_sym_for_move(t_info *info, int y, int x);
void	up_down(t_info *info, int keycode, int i);
void	left_right(t_info *info, int keycode, int i);
void	rotate_left_right(t_info *info, int keycode, double old_screen_x,
			double old_dir_x);
void	define_indent_sign(double num, int *i);
void	space_pressed(t_info *info, int x, int y, int i);

void	draw_minimap(t_info *info);
void	draw_map_pixels(t_info *info, int i, int j, int flag);
void	inside1_draw_map_pixel(t_info *info, t_map *map, int i, int j);
void	inside2_draw_map_pixel(t_info *info, t_map *map, int i, int j);
void	inside3_draw_map_pixel(t_info *info, t_map *map, int i, int j);

void	draw_opening_door(t_info *info, t_draw *draw, int i, int door_index);
void	inside_draw_opening_door(t_info *info, t_draw *draw, int i,
			int door_index);
void	draw_closing_door(t_info *info, t_draw *draw, int i, int door_index);
void	inside_draw_closing_door(t_info *info, t_draw *draw, int i,
			int door_index);
void	check_closing_door(t_info *info, int x, int y, int i);

int		rot_view(t_info *info);
void	inside_rot_view(t_info *info, double rot_speed, double old_dir_x,
			double old_screen_x);
int		for_mouse_up(int button, int x, int y, t_info *info);
int		for_mouse_down(int button, int x, int y, t_info *info);
void	draw_sprite(t_info *info, t_draw *draw, int i, int y);
void	inside_draw_sprite(t_info *info);

#endif