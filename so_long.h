/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:03:19 by marirodr          #+#    #+#             */
/*   Updated: 2024/04/08 11:32:49 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"

//S_P = sprite size
# define S_SZ 32
# define BAD_ARG 1
# define EXTENSION_ERROR 2
# define NOFILE_ERROR 3
# define EMPTY_MAP 4
# define INVALID_MAP 5
# define BAD_ROW 6
# define NO_WALLS 7
# define INVALID_ELEMENT 8
# define ELEMENT_ERROR 9
# define IMPOSIBLE_WIN 10
# define MLX_FAIL 11

typedef struct s_game
{
	char						*map_name;
	char						**map;
	char						**map_copy;
	int							num_col;
	int							num_row;
	int							player_y;
	int							player_x;
	int							curr_py;
	int							curr_px;
	int							moves;
	int							p_count;
	int							e_count;
	int							c_count;
	int							c_total;
	mlx_t						*mlx;
	mlx_image_t					*plyer_img;
	mlx_image_t					*floor_img;
	mlx_image_t					*wall_img;
	mlx_image_t					*coll_img;
	mlx_image_t					*exit_img;
}	t_game;

typedef struct s_texture
{
	mlx_texture_t		*player;
	mlx_texture_t		*floor;
	mlx_texture_t		*wall;
	mlx_texture_t		*collec;
	mlx_texture_t		*exit;
}	t_texture;

//main.c
t_game	*ft_init_strcut(char *argv, t_game *game);
void	ft_validate_map(t_game *game);

//free_n_error.c
void	ft_error(int error);
void	ft_free(t_game *game);
void	ft_print_map(t_game *game);

//map_check.c
void	ft_read_map(t_game *game, int fd);
void	ft_check_map(t_game *game);
void	ft_check_elements(t_game *game);
void	ft_flood_fill(t_game *game, int p_y, int p_x);
void	ft_valid_path(t_game *game);

//game.c
void	ft_game_start(t_game *game);
void	ft_create_window(t_game *game);
void	ft_render_map(t_game *game);
void	ft_render_player(t_game *game);

//ply_moves.c
void	ft_controls(mlx_key_data_t keydata, void *param);
void	ft_up(t_game *game);
void	ft_down(t_game *game);
void	ft_left(t_game *game);
void	ft_right(t_game *game);

//utils.c
int		ft_check_arg(char *argv);
int		ft_win(t_game *game, int y, int x);
void	ft_eat_fish(t_game *game);

#endif