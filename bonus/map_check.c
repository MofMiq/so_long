/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:31:21 by marirodr          #+#    #+#             */
/*   Updated: 2023/05/23 19:10:03 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*We read the map using get_next_line and we go line by line, retrieving all the
rows of the map. We concatenate them into another variable called tmp, so that we
have one huge line with the entire map. Then, we apply ft_split to it, generating
a clean matrix within the structure (in reality, we create two matrices because
we will later need a copy of the map when using ft_flood_fill).
Additionally, we will perform two checks: first, if the file is empty, and then
if the file starts with a '\n'*/

void	ft_read_map(t_game *game, int fd)
{
	char	*line;
	char	*tmp_map_line;

	line = get_next_line(fd);
	tmp_map_line = NULL;
	if (!line)
		ft_error(EMPTY_MAP);
	while (line)
	{
		tmp_map_line = ft_strjoin_sl(tmp_map_line, line);
		free(line);
		line = get_next_line(fd);
		game->num_row++;
	}
	if (tmp_map_line[0] == '\n')
		ft_error(INVALID_MAP);
	game->map = ft_split(tmp_map_line, '\n');
	game->map_copy = ft_split(tmp_map_line, '\n');
	free(line);
	free(tmp_map_line);
}

/*We check for two potential errors related to the maps: ensuring that all rows
have the same number of columns and checking for any gaps in the walls (absence
of '1' in the rows).*/

void	ft_check_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	game->num_col = (int)ft_strlen(game->map[0]);
	while (game->map[y])
	{
		if (game->num_col != (int)ft_strlen(game->map[y]))
			ft_error(BAD_ROW);
		x = 0;
		while (game->map[y][x])
		{
			if (y == 0 || x == 0 || y == game->num_row - 1
				|| x == game->num_col - 1)
			{
				if (game->map[y][x] != '1')
					ft_error(NO_WALLS);
			}
			x++;
		}
		y++;
	}
}

/*We verify that there are enough elements (characters) of each type: at least
one collectible ('C'), exactly one player ('P'), and exactly one exit ('E').
Additionally, we save the position of the player in the structure for later use.
We also check whether there is an undefined element in the map, such as an 'X'.
*/

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
			else if (!ft_strchr("10D", game->map[y][x]))
				ft_error(INVALID_ELEMENT);
		}
	}
	if (game->p_count != 1 || game->e_count != 1 || game->c_count < 1)
		ft_error(ELEMENT_ERROR);
}

/*ft_flood_fill should fill all '0' with 'F' starting from the player's
position ('P'). In other words, it should convert '0' and 'P' to 'F' to
check if there is a valid path to the exit ('E').
We also convert 'C' and 'E' to 0 because they are part of the valid path for
the player. Surprisingly, these conversions will serve us in the future for
another map check.
These checks must be done with game->map_copy because by painting on the map, we
are modifying it. Therefore, game->map would remain intact while still verifying
if the player has a clear path to reach the exit*/

void	ft_flood_fill(t_game *game, int p_y, int p_x)
{
	if (p_y < 0 || p_x < 0 || p_y > game->num_row
		|| p_x > game->num_col || game->map_copy[p_y][p_x] == '1'
			|| game->map_copy[p_y][p_x] == 'F'
				|| game->map_copy[p_y][p_x] == 'D')
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

/*If there is a valid path, 'C' and 'E' are converted to '0'. In other words, if
'C' and 'E' have not become '0', it means they are surrounded by walls ('1').
Therefore, if after traversing the map again, there are still any 'C' or the 'E'
intact, it means that it is not accessible for the player ('P'), making it
impossible to win.*/

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
