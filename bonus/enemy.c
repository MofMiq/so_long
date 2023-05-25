/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:43:25 by marirodr          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/23 19:53:04 by marirodr         ###   ########.fr       */
=======
/*   Updated: 2023/05/24 17:14:26 by marirodr         ###   ########.fr       */
>>>>>>> 5f007d4eab39c40bf34e3b4fc76899b1cd2b3c40
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

<<<<<<< HEAD
=======
/*This function is like ft_check_elements but for the character 'D' (the enemy).
It's not done in ft_check_elements because the 25 lines restriction (again).*/

>>>>>>> 5f007d4eab39c40bf34e3b4fc76899b1cd2b3c40
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

<<<<<<< HEAD
//	mlx_close_window(game->mlx);
=======
/*This function is for making the player character disappear and displaying a
defeat message on the screen when the player touches the enemy.*/

//mlx_close_window(game->mlx);
>>>>>>> 5f007d4eab39c40bf34e3b4fc76899b1cd2b3c40

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
<<<<<<< HEAD
=======
		game->plyer_w->instances[0].enabled = 0;
		game->plyer_s->instances[0].enabled = 0;
>>>>>>> 5f007d4eab39c40bf34e3b4fc76899b1cd2b3c40
	}
}
