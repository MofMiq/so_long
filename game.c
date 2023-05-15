/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:05:48 by marirodr          #+#    #+#             */
/*   Updated: 2023/05/15 18:28:28 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*genreamos una ventana con el tamaño que ya sabemos que tiene el mapa (num_col
& num_row) * 32, ya que es el tamaño de los sprites (mlx_init). luego generamos
las texturas a raiz de los png guardados en /img y luego las convertimos en
imagenes

¡¡¡¡¡cuidado borrar las texturas (mlx_delete_texture(texture))y las imagenes (mlx_delete_image(mlx, img))!!!!!
mlx_delete_texture(texture->player)*/

void	ft_create_window(t_game *game)
{
	t_texture	*texture;

	//ft_printf("num_col: %d\nnum_row: %d\n", game->num_col, game->num_row);
	texture = malloc(sizeof(t_texture)); //liberar memoria
	game->mlx = mlx_init(game->num_col * 32, game->num_row * 32, "so_long", 0);
	texture->player = mlx_load_png("img/cat_2.png");
	texture->floor = mlx_load_png("img/floor.png");
	texture->wall = mlx_load_png("img/wall.png");
	texture->exit = mlx_load_png("img/exit.png");
	texture->collec = mlx_load_png("img/fish.png");
	game->plyer_img = mlx_texture_to_image(game->mlx, texture->player);
	game->floor_img = mlx_texture_to_image(game->mlx, texture->floor);
	game->wall_img = mlx_texture_to_image(game->mlx, texture->wall);
	game->exit_img = mlx_texture_to_image(game->mlx, texture->exit);
	game->coll_img = mlx_texture_to_image(game->mlx, texture->collec);
	//pause();
}

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
			if (game->map[y][x] == '1')
				mlx_image_to_window(game->mlx, game->wall_img, x * 32, y * 32);
			else if (game->map[y][x] == '0')
				mlx_image_to_window(game->mlx, game->floor_img, x * 32, y * 32);
			else if (game->map[y][x] == 'C')
				mlx_image_to_window(game->mlx, game->coll_img, x * 32, y * 32);
			else if (game->map[y][x] == 'E')
				mlx_image_to_window(game->mlx, game->exit_img, x * 32, y * 32);
			else if (game->map[y][x] == 'P')
				mlx_image_to_window(game->mlx, game->plyer_img, x * 32, y * 32);
			x++;
		}
		x = 0;
		y++;
	}
}

void	ft_game_start(t_game *game)
{
	ft_create_window(game);
	ft_generate_map(game);
	//mlx_key_hook(game->mlx, &ft_controls, game);
	//mlx_loop(game->mlx);
	//mlx_terminate(game->mlx);
}
