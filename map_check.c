/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:31:21 by marirodr          #+#    #+#             */
/*   Updated: 2023/05/11 19:01:58 by marirodr         ###   ########.fr       */
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
}

void	ft_read_map(t_game *game, int fd)
{
	char	*line;
	char	*tmp_map_line;

	line = get_next_line(fd);
	tmp_map_line = NULL;
	game->num_row = 1;
	while (line)
	{
		tmp_map_line = ft_strjoin_gnl(tmp_map_line, line);
		free(line);
		line = get_next_line(fd);
		game->num_row++;
	}
	if (tmp_map_line[0] == '\0' || tmp_map_line[0] == '\n')
	{
		ft_printf("Error, the map is invalid\n");
		exit(1);
	}
	game->map = ft_split(tmp_map_line, '\n');
	game->map_copy = ft_split(tmp_map_line, '\n');
	free(line);
	free(tmp_map_line);
}

char	*ft_strjoin_map(char *old_line, char *new_line)
{
	char	*map;

	if (!old_line)
		return (ft_strdup(new_line));
	map = ft_strjoin(old_line, new_line);
	free(old_line);
	return (map);
}
