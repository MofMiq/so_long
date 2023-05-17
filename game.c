/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:05:48 by marirodr          #+#    #+#             */
/*   Updated: 2023/05/17 17:04:40 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_game_start(t_game *game)
{
	ft_create_window(game);
	ft_generate_map(game);
	ft_render_player(game);
	mlx_loop_hook(game->mlx, &ft_controls, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}

/*genreamos una ventana con el tamaño que ya sabemos que tiene el mapa (num_col
& num_row) * 32, ya que es el tamaño de los sprites (mlx_init). luego generamos
las texturas a raiz de los png guardados en /img y luego las convertimos en
imagenes

¡¡¡¡¡cuidado borrar las texturas (mlx_delete_texture(texture))y las imagenes (mlx_delete_image(mlx, img))!!!!!
mlx_delete_texture(texture->player)
//  Optional, terminate will clean up any leftover images (not textures!)
	mlx_terminate(mlx);
*/

void	ft_create_window(t_game *game)
{
	t_texture	*texture;

	texture = malloc(sizeof(t_texture)); //liberar memoria
	game->mlx = mlx_init(game->num_col * 32, game->num_row * 32, "so_long", 0);
	if (!game->mlx)
		ft_printf("Error\nmlx_init failed\n");
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
	mlx_delete_texture(texture->player);
	mlx_delete_texture(texture->floor);
	mlx_delete_texture(texture->wall);
	mlx_delete_texture(texture->exit);
	mlx_delete_texture(texture->collec);
}

/*recorremos el mapa entero y le asignamos las imagenes a cada objeto del
juego, ademas de usar la funcion mlx_image_to_window para que se muestre
en la ventana*/

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
