/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:18:23 by marirodr          #+#    #+#             */
/*   Updated: 2023/05/24 17:24:56 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_leaks(void)
{
	system("leaks -q so_long");
	exit(0);
}

t_game	*ft_init_strcut(char *argv, t_game *game)
{
	game->player_y = 0;
	game->player_x = 0;
	game->num_col = 0;
	game->num_row = 0;
	game->curr_py = 0;
	game->curr_px = 0;
	game->p_count = 0;
	game->e_count = 0;
	game->c_count = 0;
	game->enemy_c = 0;
	game->moves = 0;
	game->mlx = NULL;
	game->plyer_d = NULL;
	game->plyer_a = NULL;
	game->plyer_w = NULL;
	game->plyer_s = NULL;
	game->floor_img = NULL;
	game->wall_img = NULL;
	game->coll_img = NULL;
	game->exit_img = NULL;
	game->score = NULL;
	game->exit_cat = NULL;
	game->flag = 0;
	game->map_name = ft_strdup(argv);
	return (game);
}

/*This fucntion is to check errors in the map file.
This line: game->c_total = game->c_count isn't withing ft_check_elements
function just because the 25 lines restriction.*/

void	ft_validate_map(t_game *game)
{
	int	fd;

	fd = open(game->map_name, O_RDONLY);
	if (fd == -1)
		ft_error(NOFILE_ERROR);
	ft_read_map(game, fd);
	close(fd);
	ft_check_map(game);
	ft_check_elements(game);
	ft_check_enemy(game);
	game->c_total = game->c_count;
	ft_flood_fill(game, game->player_y, game->player_x);
	ft_valid_path(game);
	ft_game_start(game);
	ft_free(game);
	exit(0);
}

//This function start the game and it is called after the map has been validated
//mlx_loop_hook(game->mlx, &ft_controls, game);

void	ft_game_start(t_game *game)
{
	ft_create_window(game);
	ft_render_map(game);
	ft_render_player(game);
	mlx_key_hook(game->mlx, &ft_controls, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}

/*First of all, we check that the number of parameters is correct and if it's
extension is okay. Then, we initialize the structure 'game' and the we are going
to check all possible map errors before we open the window and start the game.
*/

int	main(int argc, char **argv)
{
	atexit(ft_leaks);
	t_game	*game;

	if (argc != 2)
		ft_error(BAD_ARG);
	else if (ft_check_arg(argv[1]) == 1)
		ft_error(EXTENSION_ERROR);
	game = (t_game *)malloc(sizeof(t_game));
	ft_init_strcut(argv[1], game);
	ft_validate_map(game);
}
