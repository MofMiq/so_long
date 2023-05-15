/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:31:21 by marirodr          #+#    #+#             */
/*   Updated: 2023/05/15 17:21:31 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	ft_flood_fill(game, game->player_y, game->player_x);
	ft_valid_path(game);
	ft_game_start(game);
	//ft_free_map(game);
	//exit(0);
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

/*comprobamos dos posibles errores derivados de los mapas: que todas
las filas tengan el mismo numero de columnas y que haya algun hueco 
en los muros (ausencia de '1' en los filos).*/

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

/*comprobamos que existan los suficientes elementos (caracteres) de cada tipo:
al menos un coleccionable ('C') y obligatoriamente un solo jugador ('P') y una
sola salida ('E'). Adicionalmente, guardamos en la estructura la posicion del
jugador para posteriormente usarla.*/

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

/*flood_fill debe rellenar con ‘F’ todos los ‘0’ desde la posición del jugador
(‘P’), es decir debe convertir 0 y P en F para comprobar que hay un camino
valido hacía la salida (‘E’).
Además, convertimos C y E en 0, porque forman parte del camino
Estas comprobaciones tienen que hacerse con game→map_copy porque al pintar
sobre el mapa lo estamos modificando; así game→map estaría intacto aún 
chequeando el path en caso de que haya un camino hacía la salida.*/

void	ft_flood_fill(t_game *game, int p_y, int p_x)
{
	if (p_y < 0 || p_x < 0 || p_y > game->num_row
		|| p_x > game->num_col || game->map_copy[p_y][p_x] == '1'
			|| game->map_copy[p_y][p_x] == 'F')
		return ;
	if (game->map_copy[p_y][p_x] == 'E'
			|| game->map_copy[p_y][p_x] == 'C')
		game->map_copy[p_y][p_x] = '0';
	game->map_copy[p_y][p_x] = 'F';
	ft_flood_fill(game, p_y + 1, p_x);
	ft_flood_fill(game, p_y - 1, p_x);
	ft_flood_fill(game, p_y, p_x + 1);
	ft_flood_fill(game, p_y, p_x - 1);
}

/*sí hay un camino valido C & E se convierten en 0; o lo que es lo mismo sí
C & E no han pasado a ser 0 significa que en mayor o menor medida están
rodeados de muros (1), po tanto sí al recorrer el mapa de nuevo sigue 
habiendo alguna C o la E intacta quiere decir que no es accesible para el
player (P). lo que no tiene sentido para mi ahora es empezar a recorrer
el mapa desde la posición del jugador.simplemente debo leerlo por completo.*/

void	ft_valid_path(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map_copy[++y])
	{
		x = 0;
		while (game->map_copy[y][++x])
		{
			if (game->map_copy[y][x] == 'E' || game->map_copy[y][x] == 'C')
				ft_error(IMPOSIBLE_WIN);
			x++;
		}
		y++;
	}
}
