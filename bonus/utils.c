/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:15:14 by marirodr          #+#    #+#             */
/*   Updated: 2023/05/23 19:33:07 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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
				//mlx_close_window(game->mlx);

int	ft_win(t_game *game, int y, int x)
{
	if (game->map[y][x] == 'E')
	{
		if (game->c_count == 0)
		{
			if (game->map[y][x] == 'E')
			{
				game->flag = 1;
				game->plyer_d->instances[0].enabled = 0;
				game->plyer_a->instances[0].x = 100000;
				mlx_delete_image(game->mlx, game->exit_img);
				ft_printf("YASS, 20 hours of sleep straight\n");
				return (1);
			}
		}
		else
			ft_printf("You can't rest if you're still hungry :(\n");
	}
	return (0);
}

/*esta funcion comprueba la posicion de los coleccionables y cuando una
coincide con la del jugardor, desactiva esa instancia.*/

void	ft_eat_fish(t_game *game)
{
	int	i;

	i = 0;
	game->c_count--;
	while (i < game->c_total)
	{
		if (game->coll_img->instances[i].x == game->plyer_d->instances[0].x
			&& game->coll_img->instances[i].y
			== game->plyer_d->instances[0].y)
		{	
			ft_printf("Yummy!\n");
			game->coll_img->instances[i].enabled = 0;
		}
		i++;
	}
}

void	ft_score(t_game *game)
{
	char	*str;
	char	*str2;

	str2 = ft_itoa(game->moves);
	str = ft_strjoin("Moves: ", str2);
	mlx_delete_image(game->mlx, game->score);
	game->score = mlx_put_string(game->mlx, str, 10, 10);
	free(str);
	free(str2);
}
