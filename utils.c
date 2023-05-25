/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:15:14 by marirodr          #+#    #+#             */
/*   Updated: 2023/05/25 16:59:09 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*We check if the file given as a parameter has the correct extension, which is 
.ber.*/

int	ft_check_arg(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] != '.')
		i++;
	if (ft_strcmp(&argv[i], ".ber") == 0)
		return (0);
	else
		return (1);
}

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

/*This function checks the position of the collectibles, and when one matches
the player's position, it deactivates that instance.*/

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
