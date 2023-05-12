/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:18:23 by marirodr          #+#    #+#             */
/*   Updated: 2023/05/12 17:44:51 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_leaks(void)
{
	system("leaks -q so_long");
	exit(0);
}

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
	game->new_py = 0;
	game->new_px = 0;
	game->p_count = 0;
	game->e_count = 0;
	game->c_count = 0;
	game->moves = 0;
	game->sprite_w = SPRITE_SIZE;
	game->sprite_h = SPRITE_SIZE;
	game->mlx = NULL;
	game->player_img = NULL;
	game->floor_img = NULL;
	game->wall_img = NULL;
	game->collec_img = NULL;
	game->exit_img = NULL;
	game->map_name = ft_strdup(argv);
	return (game);
}

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
