/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:15:14 by marirodr          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/22 18:51:26 by marirodr         ###   ########.fr       */
=======
/*   Updated: 2023/05/24 17:23:23 by marirodr         ###   ########.fr       */
>>>>>>> 5f007d4eab39c40bf34e3b4fc76899b1cd2b3c40
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*function that check if all collectibles have been taken, to know if you win
the game (and exit the window).*/

int	ft_win(t_game *game, int y, int x)
{
	if (game->map[y][x] == 'E')
	{
		if (game->c_count == 0)
		{
			if (game->map[y][x] == 'E')
			{
				mlx_close_window(game->mlx);
				ft_printf("YASS, 20 hours of sleep straight\n");
				return (1);
			}
		}
		else
			ft_printf("You can't rest if you're still hungry :(\n");
	}
	return (0);
}

/*mlx_put_string(game->mlx, "YOU WIN!", ((game->num_col / 2) * 32) - 48,
((game->num_row / 2) * 32)); esto pal bonus con un sleep*/

void	ft_eat_fish(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->c_total)
	{
		if (game->coll_img->instances[i].x == game->plyer_img->instances[0].x
			&& game->coll_img->instances[i].y
			== game->plyer_img->instances[0].y)
		{	
			ft_printf("Yummy!\n");
			game->coll_img->instances[i].enabled = 0;
		}
		i++;
	}
}
