/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:43:25 by marirodr          #+#    #+#             */
/*   Updated: 2023/05/25 21:10:16 by marirodr         ###   ########.fr       */
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

//mlx_close_window(game->mlx);

void	ft_you_died(t_game *game)
{
	if (game->enemy_img->instances[0].x == game->plyer_d->instances[0].x
		&& game->enemy_img->instances[0].y == game->plyer_d->instances[0].y)
	{
		game->flag = 1;
		mlx_put_string(game->mlx, "YOU DIED", ((game->num_col / 2) * 32) - 48,
			((game->num_row / 2) * 32));
		ft_printf("Bad doggy\n");
		game->plyer_d->instances[0].enabled = 0;
		game->plyer_a->instances[0].enabled = 0;
		game->plyer_w->instances[0].enabled = 0;
		game->plyer_s->instances[0].enabled = 0;
	}
}
