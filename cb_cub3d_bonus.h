/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_cub3d_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 03:57:56 by jnannie           #+#    #+#             */
/*   Updated: 2020/08/09 04:27:35 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CB_CUB3D_BONUS_H
# define CB_CUB3D_BONUS_H

# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include <limits.h>

# define CB_VALID_CHARS "0123 NSWE"

# define CB_ERR_NO_ARG "there should be *.cub file as first argument"
# define CB_ERR_INIT "some error during initialization"
# define CB_ERR_WIN "window creating error"
# define CB_ERR_READ_FILE "reading map file error"
# define CB_ERR_MAP_FILE "map file is wrong"
# define CB_ERR_MAP "map is wrong"
# define CB_ERR_RESOLUTION "resolution line is wrong"
# define CB_ERR_TEXTURE "texture reading error"
# define CB_ERR_COLOR "color line is wrong"
# define CB_ERR_IMAGE_SAVE "error during image saving"

# define CB_IMAGE_FILENAME "frame.bmp"
# define CB_WINDOW_TITLE "cub3D"
# define CB_PLANE_LENGTH 0.66

typedef struct		s_bmp_file_header
{
	unsigned char	bitmap_type[2];
	int				file_size;
	short			reserved1;
	short			reserved2;
	unsigned int	offset_bits;
}					t_bmp_file_header;

typedef struct		s_bmp_image_header
{
	unsigned int	size_header;
	unsigned int	width;
	unsigned int	height;
	short int		color_planes;
	short int		bitsperpixel;
	unsigned int	compression;
	unsigned int	image_size;
	unsigned int	ppm_x;
	unsigned int	ppm_y;
	unsigned int	numcolorspallette;
	unsigned int	numcolorsused;
}					t_bmp_image_header;

typedef	struct		s_cbscreen
{
	int				frame_x;
	int				frame_y;
	int				frame_start_y;
	int				frame_end_y;
	int				frame_start_x;
	int				frame_end_x;
	int				tex_x;
	int				tex_y;
	int				line_height;
	int				line_width;
	int				frame_pix;
	int				tex_pix;
}					t_cbscreen;

typedef	struct		s_cbraycaster
{
	double			plane_step;
	double			ray_x;
	double			ray_y;
	long			map_x;
	long			map_y;
	double			dist_x;
	double			dist_y;
	int				step_x;
	int				step_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				wall_side;
	double			*perp_dists;
}					t_cbraycaster;

typedef	struct		s_cbimage
{
	void			*img_ptr;
	char			*image;
	int				endian;
	int				size_line;
	int				bits_per_pixel;
	int				width;
	int				height;
}					t_cbimage;

typedef struct		s_sprite
{
	double			x;
	double			y;
	double			dist;
	t_cbimage		*sprite;
}					t_sprite;

typedef	struct		s_cbdata
{
	void			*mlx_ptr;
	void			*win_ptr;
	char			**map;
	t_cbimage		*frame;
	t_cbimage		*no_texture;
	t_cbimage		*so_texture;
	t_cbimage		*we_texture;
	t_cbimage		*ea_texture;
	t_cbimage		*sprite;
	t_cbimage		*bonus_sprite;
	unsigned int	floor_color;
	unsigned int	ceilling_color;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			dir_x_perp;
	double			dir_y_perp;
	double			plane_x;
	double			plane_y;
	int				map_fd;
	char			*line;
	int				key_rot_left;
	int				key_rot_right;
	int				key_left;
	int				key_right;
	int				key_up;
	int				key_down;
	int				key_w;
	int				key_s;
	double			move_speed;
	double			rotate_speed;
	t_sprite		*sprites;
	long			sprites_num;
	t_cbraycaster	*rc;
	t_cbscreen		*sc;
	long			cur_spr;
}					t_cbdata;

int					cb_key_press_hook(int keycode, t_cbdata *cb);
int					cb_key_release_hook(int keycode, t_cbdata *cb);
int					cb_destroy_hook(t_cbdata *cb);
int					cb_expose_hook(t_cbdata *cb);
int					cb_loop_hook(t_cbdata *cb);

int					cb_parse_map_file(t_cbdata *cb, char *filename);
void				cb_free_map(char **map);
void				cb_exit(t_cbdata *cb, char *err_msg);
int					cb_parse_map(t_cbdata *cb);
void				cb_parse_settings_line(t_cbdata *cb, char *line);
int					cb_read_color(t_cbdata *cb, char *line);
void				cb_print_map(char **map);
int					cb_check_walls(t_cbdata *cb);

void				cb_rotate_vectors(t_cbdata *cb, double angle);
void				cb_move(t_cbdata *cb, double dir_x, double dir_y, int dir);

void				cb_draw_frame(t_cbdata *cb);
void				cb_print_floor_and_ceilling(t_cbdata *cb);
void				cb_draw_sprites(t_cbdata *cb);
void				cb_draw_walls(t_cbdata *cb);
void				cb_draw_wall_line(t_cbdata *cb, t_cbimage *texture);
double				cb_wall_coord(t_cbdata *cb);
void				cb_find_wall(t_cbdata *cb, t_cbraycaster *rc);

int					cb_save_frame(t_cbdata *cb);

#endif
