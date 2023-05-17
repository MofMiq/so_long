/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ply_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:33:58 by marirodr          #+#    #+#             */
/*   Updated: 2023/05/17 17:33:33 by marirodr         ###   ########.fr       */
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
	game->curr_py = game->plyer_img->instances[0].y / 32;
	game->curr_px = game->plyer_img->instances[0].x / 32;
	//recalculamos l aposicion del jugador en el mapa atraves de la instancia de la imagen / el tamaño de los sprites
	//ft_printf("curr_px: %d, curr_py: %d\n", game->curr_px, game->curr_py);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (game->is_pressed == 0)
	{
		if (mlx_is_key_down(game->mlx, MLX_KEY_W))
			ft_up(game);
		if (mlx_is_key_down(game->mlx, MLX_KEY_S))
			ft_down(game);
		if (mlx_is_key_down(game->mlx, MLX_KEY_A))
			ft_left(game);
		if (mlx_is_key_down(game->mlx, MLX_KEY_D))
			ft_right(game);
	}
	if (!mlx_is_key_down(game->mlx, MLX_KEY_W) && !mlx_is_key_down(game->mlx, MLX_KEY_S) && !mlx_is_key_down(game->mlx, MLX_KEY_A) && !mlx_is_key_down(game->mlx, MLX_KEY_D))
		game->is_pressed = 0;
}

void	ft_up(t_game *game)
{
	if (game->map[game->curr_py - 1][game->curr_px] == '1')
		return ;
	if (game->map[game->curr_py - 1][game->curr_px] == 'C')
	{
		game->c_count--; //
		ft_printf("Fishes eaten\n");
	}
	game->plyer_img->instances[0].y -= 32;
	game->curr_py--;
	game->moves++;
	game->is_pressed = 1;
	ft_printf("Moves: %d\n", game->moves);
}

void	ft_down(t_game *game)
{
	if (game->map[game->curr_py + 1][game->curr_px] == '1')
		return ;
	if (game->map[game->curr_py + 1][game->curr_px] == 'C')
	{
		game->c_count--;
		ft_printf("Fishes eaten\n");
	}
	game->plyer_img->instances[0].y += 32;
	game->curr_py++;
	game->moves++;
	game->is_pressed = 1;
	ft_printf("Moves: %d\n", game->moves);
}

void	ft_left(t_game *game)
{
	if (game->map[game->curr_py][game->curr_px - 1] == '1')
		return ;
	if (game->map[game->curr_py][game->curr_px - 1] == 'C')
	{
		game->c_count--; //
		ft_printf("Fishes eaten\n");
	}
	game->plyer_img->instances[0].x -= 32;
	game->curr_px--;
	game->moves++;
	game->is_pressed = 1;
	ft_printf("Moves: %d\n", game->moves);
}

void	ft_right(t_game *game)
{
	if (game->map[game->curr_py][game->curr_px + 1] == '1')
		return ;
	if (game->map[game->curr_py][game->curr_px + 1] == 'C')
	{
		game->c_count--; //
		ft_printf("Fishes eaten\n");
	}
	game->plyer_img->instances[0].x += 32;
	game->curr_px++;
	game->moves++;
	game->is_pressed = 1;
	ft_printf("Moves: %d\n", game->moves);
}
