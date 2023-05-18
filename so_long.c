/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:18:23 by marirodr          #+#    #+#             */
/*   Updated: 2023/05/17 16:45:59 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_leaks(void)
{
	system("leaks -q so_long");
	exit(0);
}

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

t_game	*ft_init_strcut(char *argv, t_game *game)
{
	game->player_y = 0;
	game->player_x = 0;
	game->num_col = 0;
	game->num_row = 0;
	game->map_y = 0;
	game->map_x = 0;
	game->curr_py = 0;
	game->curr_px = 0;
	game->p_count = 0;
	game->e_count = 0;
	game->c_count = 0;
	game->moves = 0;
	game->sprite_w = S_SZ;
	game->sprite_h = S_SZ;
	game->is_pressed = 0;
	game->mlx = NULL;
	game->plyer_img = NULL;
	game->floor_img = NULL;
	game->wall_img = NULL;
	game->coll_img = NULL;
	game->exit_img = NULL;
	game->map_name = ft_strdup(argv);
	return (game);
}

/*First of all, we check that the number of parameters is correct and if it's
extension is okay. Then, we initialize the structure 'game' and the we are going
to check all possible map errors before we open the window and start the game.*/

int	main(int argc, char **argv)
{
	atexit(ft_leaks);
	t_game	*game;

	if (argc != 2)
	{
		ft_printf("Error, wrong number of arguments\n");
		exit(1);
	}
	else if (ft_check_arg(argv[1]) == 1)
	{
		ft_printf("Error, the file extension isn't .ber\n");
		exit(1);
	}
	game = (t_game *)malloc(sizeof(t_game)); //reservo la memoria para la estructura
	ft_init_strcut(argv[1], game); //inicializo la estructura
	ft_map_check(game);
	//ft_free(game);
}
