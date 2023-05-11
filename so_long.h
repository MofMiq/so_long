/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:03:19 by marirodr          #+#    #+#             */
/*   Updated: 2023/05/11 18:56:54 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"

# define SPRITE_SIZE 32
# define NOFILE_ERROR 3
# define EMPTY_MAP 4
# define INVALID_MAP 5
# define BAD_ROW 6
# define NO_WALLS 7
# define INVALID_ELEMENT 8
# define ELEMENT_ERROR 9

typedef struct s_game
{
	char				*map_name;
	char				**map;
	char				**map_copy;
	int					map_y;
	int					map_x;
	int					num_col; //y
	int					num_row; //x	
	int					player_y;
	int					player_x;
	int					new_py;
	int					new_px;
	int					moves;
	int					p_count;
	int					e_count;
	int					c_count;
	int					sprite_w;
	int					sprite_h;
 	mlx_t	*mlx;
	mlx_image_t			*player_img;
	mlx_image_t			*floor_img;
	mlx_image_t			*wall_img;
	mlx_image_t			*collec_img;
	mlx_image_t			*exit_img;
}	t_game;

typedef struct s_texture
{
	mlx_image_t			*player;
	mlx_image_t			*floor;
	mlx_image_t			*wall;
	mlx_image_t			*collec;
	mlx_image_t			*exit;
}	t_texture;

//main.c
int		ft_check_arg(char *argv);
t_game	*ft_init_strcut(char *argv, t_game *game);

//free_n_error.c
void	ft_error(int error, t_game *game);
void	ft_free(t_game *game);

//map_check.c
void	ft_map_check(t_game *game);
void	ft_read_map(t_game *game, int fd);
char	*ft_strjoin_map(char *old_line, char *new_line);

#endif