/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ply_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:33:58 by marirodr          #+#    #+#             */
/*   Updated: 2023/05/16 18:50:49 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*esta funcion simplemente pilla la tecla del teclado que se esta presionando,
como está siendo presionada y le asigna un movimiento dentro del mapa. Creamos
la orden por decirlo asi, pero en si misma no hace ningun movimiento porque para
eso hay que llamar a la funcion mlx_is_key_down*/

void	ft_controls(void *param)
{
	t_game	*game;

	game = param;
	game->curr_py = game->player_y;
	game->curr_px = game->player_x;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		ft_up(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		ft_down(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		ft_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		ft_right(game);
}

void	ft_up(t_game *game)
{
	if (game->map[game->curr_py - 1][game->curr_px] == '1')
		return ;
	if (game->map[game->curr_py - 1][game->curr_px] == 'C')
	{
		game->c_count--; //
		game->map[game->curr_py - 1][game->curr_px] = '0';
		ft_printf("Fishes eaten");
	}
	game->plyer_img->instances[0].y -= 32;
	game->curr_py--;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
}

void	ft_down(t_game *game)
{
	if (game->map[game->curr_py + 1][game->curr_px] == '1')
		return ;
	if (game->map[game->curr_py + 1][game->curr_px] == 'C')
	{
		game->c_count--; //
		game->map[game->curr_py + 1][game->curr_px] = '0';
		ft_printf("Fishes eaten");
	}
	game->plyer_img->instances[0].y += 32;
	game->curr_py++;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
}

void	ft_left(t_game *game)
{
	if (game->map[game->curr_py][game->curr_px - 1] == '1')
		return ;
	if (game->map[game->curr_py][game->curr_px - 1] == 'C')
	{
		game->c_count--; //
		game->map[game->curr_py][game->curr_px - 1] = '0';
		ft_printf("Fishes eaten");
	}
	game->plyer_img->instances[0].x -= 32;
	game->curr_px--;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
}

void	ft_right(t_game *game)
{
	if (game->map[game->curr_py][game->curr_px + 1] == '1')
		return ;
	if (game->map[game->curr_py][game->curr_px + 1] == 'C')
	{
		game->c_count--; //
		game->map[game->curr_py][game->curr_px + 1] = '0';
		ft_printf("Fishes eaten");
	}
	game->plyer_img->instances[0].x += 32;
	game->curr_px++;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
}

/*void	ft_controls(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	game->curr_py = game->player_y;
	game->curr_px = game->player_x;
	ft_printf("curr_py: %d\nnew_px: %d\n", game->curr_py, game->curr_px);
	if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		game->curr_py--;
	if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		game->curr_py++;
	if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
		game->curr_px--;
	if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		game->curr_px++;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(game->mlx);
		exit(0); //??
	}
	ft_real_moves()
}*/
