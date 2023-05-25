/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ply_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:33:58 by marirodr          #+#    #+#             */
/*   Updated: 2023/05/23 19:50:52 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*This function simply captures the keyboard key that is being pressed and then
calls another function that specifies how the movement will occur within the map
(creating the corresponding command). Additionally, we assign a function to the
ESC key that closes the game and the window.
We calculate the player's position in the map through the instance, which is the
image and we divide it by the size of the sprites.
To ensure that the player moves one cell at a time instead of continuously, we
create a boolean variable called 'is_pressed' within the 'game' structure that
prevents excessive movements.*/

void	ft_controls(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	game->curr_py = game->plyer_d->instances[0].y / 32;
	game->curr_px = game->plyer_d->instances[0].x / 32;
	if (game->flag == 0)
	{
		if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
			ft_up(game);
		if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
			ft_down(game);
		if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
			ft_left(game);
		if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
			ft_right(game);
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(game->mlx);
}

/*The 'up' movement is executed when we press 'W'. Here's how it is defined:
If the player encounters a '1' (wall), the movement is terminated, and the
character doesn't advance.
If the player encounters a collectible, the ft_collectibles function is executed.
For any other case, the following steps are performed:
1 - Move the image through the instance in the desired direction.
2 - Update the player's position on the map based on '1' and '0'.
3 - Increment the player's total movement count by one in 'moves'.
4 - Set the boolean variable is_pressed to 1 to prevent additional movements from
being executed.*/

void	ft_up(t_game *game)
{
	if (game->map[game->curr_py - 1][game->curr_px] == '1'
		|| (game->map[game->curr_py - 1][game->curr_px] == 'E'
			&& ft_win(game, game->curr_py - 1, game->curr_px)))
		return ;
	game->plyer_d->instances[0].y -= 32;
	game->plyer_a->instances[0].y -= 32;
	if (game->map[game->curr_py - 1][game->curr_px] == 'D')
		ft_you_died(game);
	if (game->map[game->curr_py - 1][game->curr_px] == 'C')
		ft_eat_fish(game);
	game->map[game->curr_py][game->curr_px] = '0';
	game->map[game->curr_py - 1][game->curr_px] = 'P';
	game->curr_py--;
	game->moves++;
	ft_score(game);
	ft_printf("Moves: %d\n", game->moves);
}

//The 'down' movement is executed when we press 'S'. Idem.

void	ft_down(t_game *game)
{
	if (game->map[game->curr_py + 1][game->curr_px] == '1'
		|| (game->map[game->curr_py + 1][game->curr_px] == 'E'
			&& !ft_win(game, game->curr_py + 1, game->curr_px)))
		return ;
	game->plyer_d->instances[0].y += 32;
	game->plyer_a->instances[0].y += 32;
	if (game->map[game->curr_py + 1][game->curr_px] == 'D')
		ft_you_died(game);
	if (game->map[game->curr_py + 1][game->curr_px] == 'C')
		ft_eat_fish(game);
	game->map[game->curr_py][game->curr_px] = '0';
	game->map[game->curr_py + 1][game->curr_px] = 'P';
	game->curr_py++;
	game->moves++;
	ft_score(game);
	ft_printf("Moves: %d\n", game->moves);
}

//The 'left' movement is executed when we press 'A'. Idem.

void	ft_left(t_game *game)
{

	if (game->map[game->curr_py][game->curr_px - 1] == '1'
		|| (game->map[game->curr_py][game->curr_px - 1] == 'E'
			&& !ft_win(game, game->curr_py, game->curr_px - 1)))
		return ;
	game->plyer_d->instances[0].x -= 32;
	game->plyer_a->instances[0].x -= 32;
	game->plyer_d->instances[0].enabled = 0;
	game->plyer_a->instances[0].enabled = 1;
	if (game->map[game->curr_py][game->curr_px - 1] == 'D')
		ft_you_died(game);
	if (game->map[game->curr_py][game->curr_px - 1] == 'C')
		ft_eat_fish(game);
	game->map[game->curr_py][game->curr_px] = '0';
	game->map[game->curr_py][game->curr_px - 1] = 'P';
	game->curr_px--;
	game->moves++;
	ft_score(game);
	ft_printf("Moves: %d\n", game->moves);
}

//The 'right' movement is executed when we press 'D'. Idem.

void	ft_right(t_game *game)
{
	if (game->map[game->curr_py][game->curr_px + 1] == '1'
		|| (game->map[game->curr_py][game->curr_px + 1] == 'E'
			&& !ft_win(game, game->curr_py, game->curr_px + 1)))
		return ;
	game->plyer_d->instances[0].x += 32;
	game->plyer_a->instances[0].x += 32;
	game->plyer_d->instances[0].enabled = 1;
	game->plyer_a->instances[0].enabled = 0;
	if (game->map[game->curr_py][game->curr_px + 1] == 'D')
		ft_you_died(game);
	if (game->map[game->curr_py][game->curr_px + 1] == 'C')
		ft_eat_fish(game);
	game->map[game->curr_py][game->curr_px] = '0';
	game->map[game->curr_py][game->curr_px + 1] = 'P';
	game->curr_px++;
	game->moves++;
	ft_score(game);
	ft_printf("Moves: %d\n", game->moves);
}
