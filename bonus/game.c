/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:05:48 by marirodr          #+#    #+#             */
/*   Updated: 2023/05/22 18:49:55 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

//This function start the game and it is called after the map has been validated
//mlx_loop_hook(game->mlx, &ft_controls, game);

void	ft_game_start(t_game *game)
{
	ft_create_window(game);
	ft_generate_map(game);
	ft_render_player(game);
	mlx_key_hook(game->mlx, &ft_controls, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}

/*We generate a window with the size we already know the map has (num_col &
num_row) * 32, as it is the size of the sprites in mlx_init. Then, we generate
the textures based on the PNG files stored in /img and convert them into images
that can be displayed on the window.
We need to manually delete the textures to avoid residual garbage, so we do it
in this function directly once they have been converted into images. On the other
hand, we don't need to manually delete the images because mlx_terminate takes
care of it for us. */

void	ft_create_window(t_game *game)
{
	t_texture	*texture;

	texture = malloc(sizeof(t_texture));
	game->mlx = mlx_init(game->num_col * 32, game->num_row * 32, "so_long", 0);
	if (!game->mlx)
		ft_printf("Error\nmlx_init failed\n");
	texture->player = mlx_load_png("img/cat_32.png");
	texture->floor = mlx_load_png("img/floor.png");
	texture->wall = mlx_load_png("img/wall.png");
	texture->exit = mlx_load_png("img/exit.png");
	texture->collec = mlx_load_png("img/fish.png");
	if (!texture->player || !texture->floor || !texture->wall
		|| !texture->exit || !texture->collec)
		ft_error(MLX_FAIL);
	game->plyer_img = mlx_texture_to_image(game->mlx, texture->player);
	game->floor_img = mlx_texture_to_image(game->mlx, texture->floor);
	game->wall_img = mlx_texture_to_image(game->mlx, texture->wall);
	game->exit_img = mlx_texture_to_image(game->mlx, texture->exit);
	game->coll_img = mlx_texture_to_image(game->mlx, texture->collec);
	mlx_delete_texture(texture->player);
	mlx_delete_texture(texture->floor);
	mlx_delete_texture(texture->wall);
	mlx_delete_texture(texture->exit);
	mlx_delete_texture(texture->collec);
	free(texture);
}

/*We traverse the entire map and assign the images to each object in the game,
in addition to using the function mlx_image_to_window to display it in the
window.
We also first place the floor image in all cells to ensure that the remaining
sprites don't appear "hanging in the air" or without a base.*/

void	ft_generate_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (game->map[y])
	{
		while (game->map[y][x])
		{
			mlx_image_to_window(game->mlx, game->floor_img, x * 32, y * 32);
			if (game->map[y][x] == '1')
				mlx_image_to_window(game->mlx, game->wall_img, x * 32, y * 32);
			else if (game->map[y][x] == 'C')
				mlx_image_to_window(game->mlx, game->coll_img, x * 32, y * 32);
			else if (game->map[y][x] == 'E')
				mlx_image_to_window(game->mlx, game->exit_img, x * 32, y * 32);
			x++;
		}
		x = 0;
		y++;
	}
}

/*We assign the image to the player (P) separately to ensure that it remains on
top of the layers assigned by mlx, preventing it from "disappearing" beneath the
layers of other sprites.*/

void	ft_render_player(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (game->map[y])
	{
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'P')
				mlx_image_to_window(game->mlx, game->plyer_img, x * 32, y * 32);
			x++;
		}
		x = 0;
		y++;
	}
}
