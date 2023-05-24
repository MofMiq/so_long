/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:05:48 by marirodr          #+#    #+#             */
/*   Updated: 2023/05/24 16:24:11 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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
	texture->player = mlx_load_png("img/cat_d.png");
	texture->player_a = mlx_load_png("img/cat_a.png");
	texture->player_w = mlx_load_png("img/cat_w.png");
	texture->player_s = mlx_load_png("img/cat_s.png");
	texture->floor = mlx_load_png("img/floor.png");
	texture->wall = mlx_load_png("img/wall.png");
	texture->exit = mlx_load_png("img/exit.png");
	texture->collec = mlx_load_png("img/fish.png");
	texture->exit_cat = mlx_load_png("img/exit_cat.png");
	texture->enemy = mlx_load_png("img/dog_2.png");
	if (!texture->player || !texture->floor || !texture->wall
		|| !texture->exit || !texture->collec || !texture->exit_cat
		|| !texture->player_a || !texture->enemy || !texture->player_w
		|| !texture->player_s)
		ft_error(MLX_FAIL);
	ft_texture_to_image(game, texture);
	ft_delete_texture(texture);
}

void	ft_texture_to_image(t_game *game, t_texture *texture)
{
	game->plyer_d = mlx_texture_to_image(game->mlx, texture->player);
	game->plyer_a = mlx_texture_to_image(game->mlx, texture->player_a);
	game->plyer_w = mlx_texture_to_image(game->mlx, texture->player_w);
	game->plyer_s = mlx_texture_to_image(game->mlx, texture->player_s);
	game->floor_img = mlx_texture_to_image(game->mlx, texture->floor);
	game->wall_img = mlx_texture_to_image(game->mlx, texture->wall);
	game->exit_img = mlx_texture_to_image(game->mlx, texture->exit);
	game->coll_img = mlx_texture_to_image(game->mlx, texture->collec);
	game->exit_cat = mlx_texture_to_image(game->mlx, texture->exit_cat);
	game->enemy_img = mlx_texture_to_image(game->mlx, texture->enemy);
}

void	ft_delete_texture(t_texture *texture)
{
	mlx_delete_texture(texture->player);
	mlx_delete_texture(texture->player_a);
	mlx_delete_texture(texture->player_w);
	mlx_delete_texture(texture->player_s);
	mlx_delete_texture(texture->floor);
	mlx_delete_texture(texture->wall);
	mlx_delete_texture(texture->exit);
	mlx_delete_texture(texture->collec);
	mlx_delete_texture(texture->exit_cat);
	mlx_delete_texture(texture->enemy);
	free(texture);
}

/*We traverse the entire map and assign the images to each object in the game,
in addition to using the function mlx_image_to_window to display it in the
window.
We also first place the floor image in all cells to ensure that the remaining
sprites don't appear "hanging in the air" or without a base.*/

void	ft_render_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			mlx_image_to_window(game->mlx, game->floor_img, x * 32, y * 32);
			if (game->map[y][x] == '1')
				mlx_image_to_window(game->mlx, game->wall_img, x * 32, y * 32);
			else if (game->map[y][x] == 'C')
				mlx_image_to_window(game->mlx, game->coll_img, x * 32, y * 32);
			else if (game->map[y][x] == 'E')
			{
				mlx_image_to_window(game->mlx, game->exit_cat, x * 32, y * 32);
				mlx_image_to_window(game->mlx, game->exit_img, x * 32, y * 32);
			}
			else if (game->map[y][x] == 'D')
				mlx_image_to_window(game->mlx, game->enemy_img, x * 32, y * 32);
			x++;
		}
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
			{
				mlx_image_to_window(game->mlx, game->plyer_d, x * 32, y * 32);
				mlx_image_to_window(game->mlx, game->plyer_a, x * 32, y * 32);
				mlx_image_to_window(game->mlx, game->plyer_w, x * 32, y * 32);
				mlx_image_to_window(game->mlx, game->plyer_s, x * 32, y * 32);
				game->plyer_a->instances[0].enabled = 0;
				game->plyer_w->instances[0].enabled = 0;
				game->plyer_s->instances[0].enabled = 0;
			}
			x++;
		}
		x = 0;
		y++;
	}
}
