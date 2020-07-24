/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 03:57:56 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/24 12:47:30 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CB_CUB3D_H
# define CB_CUB3D_H

# include <errno.h>
# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <fcntl.h>

# define CB_VALID_CHARS "012 NSWE"

# define CB_ERR_NO_ARG "there should be *.cub file as first argument"
# define CB_ERR_INIT "some error during initialization"
# define CB_ERR_WIN "window creating error"
# define CB_ERR_READ_FILE "reading map file error"
# define CB_ERR_MAP_FILE "map file is wrong"
# define CB_ERR_MAP "map is wrong"
# define CB_ERR_RESOLUTION "resolution line is wrong"
# define CB_ERR_TEXTURE "texture reading error"
# define CB_ERR_COLOR "color line is wrong"

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

typedef	struct		s_cbdata
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*frame_ptr;
	char			**map;
	t_cbimage		*no_texture;
	t_cbimage		*so_texture;
	t_cbimage		*we_texture;
	t_cbimage		*ea_texture;
	t_cbimage		*sprite;
	int				win_width;
	int				win_height;
	unsigned int	floor_color;
	unsigned int	ceilling_color;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
//	int				cb_err;
	int				fd;
	char			*line;
}					t_cbdata;

//int			cb_expose_hook(void *map);
int				cb_key_hook(int keycode,void *map);
//int			cb_mouse_hook(int button,int x,int y,void *map);
//int			cb_loop_hook(void *map);
int				cb_parse_map_file(t_cbdata *cbdata, char *filename);
void			cb_free_map(char **map);
int				get_next_line(int fd, char **line);
void			cb_print_err(char *err_msg);//, int err);
int				cb_free_get_next_line_buf(int fd);
void			cb_exit(t_cbdata *cbdata, char *err_msg);//, int err);
int				cb_parse_map(t_cbdata *cbdata);
void			cb_parse_settings_line(t_cbdata *cbdata, char *line);

#endif