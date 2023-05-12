/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:31:21 by marirodr          #+#    #+#             */
/*   Updated: 2023/05/12 18:42:45 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//for debug only
void	ft_print_map(t_game *game)
{
	int	i;

	i = 0;
	ft_printf("map:\n");
	while (game->map[i])
	{
		ft_printf("%s\n", game->map[i]);
		i++;
	}
	i = 0;
	ft_printf("map_copy:\n");
	while (game->map_copy[i])
	{
		ft_printf("%s\n", game->map_copy[i]);
		i++;
	}
}

void	ft_map_check(t_game *game)
{
	int	fd;

	fd = open(game->map_name, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error, the file doesn't exist\n");
		exit(1);
	}
	ft_read_map(game, fd);
	close(fd);
	ft_check_map(game);
	ft_check_elements(game);
}

/*leemos el mapa con get_next_line y vamos cogiendo linea a linea todas
las filas del mapa. las vamos concatenando en otra variable tmp, de modo
que quede una linea enorme con todo el mapa, para despues aplicarle el
ft_split y generar una matriz limpia en la estructua (dos, si contamos
la copia del mapa que usaremos cuando el flood fill)*/

void	ft_read_map(t_game *game, int fd)
{
	char	*line;
	char	*tmp_map_line;

	line = get_next_line(fd);
	tmp_map_line = NULL;
	if (!line) //check if the map's file is empty
		ft_error(EMPTY_MAP);
	while (line)
	{
		tmp_map_line = ft_strjoin_sl(tmp_map_line, line);
		free(line);
		line = get_next_line(fd);
		game->num_row++;
	}
	if (tmp_map_line[0] == '\n') //formato del mapa invalido porque empiza con salto de linea
		ft_error(INVALID_MAP);
	game->map = ft_split(tmp_map_line, '\n');
	game->map_copy = ft_split(tmp_map_line, '\n');
	free(line);
	free(tmp_map_line);
}

void	ft_check_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	game->num_col = (int)ft_strlen(game->map[0]); //ok, we check and save in the struct the number of columns
	while (game->map[y])
	{
		if (game->num_col != (int)ft_strlen(game->map[y])) //check if the number of columns is the same in all rows
			ft_error(BAD_ROW);
		x = 0;
		while(game->map[y][x])
		{
			if (y == 0 || x == 0 || y == game->num_row - 1 || x == game->num_col - 1) //check if the map is surrounded by walls
			{
				if (game->map[y][x] != '1')
					ft_error(NO_WALLS);
			}
			x++;
		}
		y++;
	}
}

void	ft_check_elements(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[++y])
	{
		x = 0;
		while (game->map[y][++x])
		{
			if (game->map[y][x] == 'P')
			{
				game->p_count++;
				game->player_y = y;
				game->player_x = x;
			}
			else if (game->map[y][x] == 'E')
				game->e_count++;
			else if (game->map[y][x] == 'C')
				game->c_count++;
			else if (game->map[y][x] != '0' && game->map[y][x] != '1')
				ft_error(INVALID_ELEMENT);
		}
	}
	if (game->p_count != 1 || game->e_count != 1 || game->c_count < 1)
		ft_error(ELEMENT_ERROR);
}
