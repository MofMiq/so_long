/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:43:25 by marirodr          #+#    #+#             */
/*   Updated: 2023/05/23 19:53:04 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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

//	mlx_close_window(game->mlx);

void	ft_you_died(t_game *game)
{
	if (game->enemy_img->instances[0].x == game->plyer_d->instances[0].x
		&& game->enemy_img->instances[0].y == game->plyer_d->instances[0].y)
	{
		mlx_put_string(game->mlx, "YOU DIED", ((game->num_col / 2) * 32) - 48,
			((game->num_row / 2) * 32));
		ft_printf("Bad doggy\n");
		game->plyer_d->instances[0].enabled = 0;
		game->plyer_a->instances[0].enabled = 0;
	}
}
