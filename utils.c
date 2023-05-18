/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:15:14 by marirodr          #+#    #+#             */
/*   Updated: 2023/05/18 18:34:09 by marirodr         ###   ########.fr       */
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
			//ft_printf("You can rest now :)\n"); esto pa la fucnion ft_collectibles
			if (game->map[y][x] == 'E')
			{
				//mlx_put_string(game->mlx, "YOU WIN!", ((game->num_col / 2) * 32) - 48, ((game->num_row / 2) * 32)); esto pal bonus con un sleep
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
