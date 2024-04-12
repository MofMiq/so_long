/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:43:25 by marirodr          #+#    #+#             */
/*   Updated: 2024/04/12 15:25:35 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*This function is like ft_check_elements but for the character 'D' (the enemy).
It's not done in ft_check_elements because the 25 lines restriction (again).*/

void	ft_check_enemy(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[++y])
	{
		x = 0;
		while (game->map[y][++x])
		{
			if (game->map[y][x] == 'D')
				game->enemy_c++;
		}
	}
	if (game->enemy_c < 1)
		ft_error(ELEMENT_ERROR);
}

/*This function is for making the player character disappear and displaying a
defeat message on the screen when the player touches the enemy.*/

void	ft_you_died(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemy_c)
	{
		if (game->enemy_img->instances[i].x == game->plyer_d->instances[0].x
			&& game->enemy_img->instances[i].y == game->plyer_d->instances[0].y)
		{
			ft_printf("Bad doggy\n");
			ft_printf("\033[31mYOU DIED\033[0m\n");
			mlx_close_window(game->mlx);
			break ;
		}
		i++;
	}
}

void	ft_render_enemy(t_game *game, int y, int x, int *enemy)
{
	mlx_image_to_window(game->mlx, game->enemy_img, x * 32, y * 32);
	mlx_image_to_window(game->mlx, game->enemy_right_img, x * 32, y * 32);
	game->enemy_img->instances[(*enemy)].z = 100;
	game->enemy_right_img->instances[(*enemy)].z = 100;
	game->enemy_right_img->instances[(*enemy)].enabled = false;
	(*enemy)++;
}

void	ft_enemy_left(t_game *game, int y, int x, int i)
{
	if (game->map[y][x - 1] != '1' && game->map[y][x - 1] != 'C')
	{
		game->map[y][x] = '0';
		game->map[y][x - 1] = 'D';
		game->enemy_img->instances[i].x -= 32;
		game->enemy_right_img->instances[i].x -= 32;
		return ;
	}
	else
	{
		game->enemy_img->instances[i].enabled = false;
		game->enemy_right_img->instances[i].enabled = true;
	}
}

void	ft_enemy_right(t_game *game, int y, int x, int i)
{
	if (game->map[y][x + 1] != '1' && game->map[y][x + 1] != 'C')
	{
		game->map[y][x] = '0';
		game->map[y][x + 1] = 'D';
		game->enemy_img->instances[i].x += 32;
		game->enemy_right_img->instances[i].x += 32;
		return ;
	}
	else
	{
		game->enemy_img->instances[i].enabled = true;
		game->enemy_right_img->instances[i].enabled = false;
	}
}
