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

/*This function simply captures the keyboard key that is being pressed and then
calls another function that specifies how the movement will occur within the map
(creating the corresponding command). Additionally, we assign a function to the
ESC key that closes the game and the window.
We calculate the player's position in the map through the instance, which is the
image and we divide it by the size of the sprites.
To ensure that the player moves one cell at a time instead of continuously, we
create a boolean variable called 'is_pressed' within the 'game' structure that
prevents excessive movements.*/

void	ft_controls(void *param)
{
	t_game	*game;

	game = param;
	game->curr_py = game->plyer_img->instances[0].y / 32;
	game->curr_px = game->plyer_img->instances[0].x / 32;
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

/*The 'up' movement is executed when we press 'W'. Here's how it is defined:
If the player encounters a '1' (wall), the movement is terminated, and the
character doesn't advance.
If the player encounters a collectible, the ft_collectibles function is executed.
For any other case, the following steps are performed:
Move the image through the instance in the desired direction.
Update the player's position on the map based on '1' and '0'.
Increment the player's total movement count by one in 'moves'.
Set the boolean variable is_pressed to 1 to prevent additional movements from
being executed.*/

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

//The 'down' movement is executed when we press 'S'. Idem.

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

//The 'left' movement is executed when we press 'A'. Idem.

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

//The 'right' movement is executed when we press 'D'. Idem.

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
