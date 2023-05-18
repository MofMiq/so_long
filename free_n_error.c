/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_n_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:00:21 by marirodr          #+#    #+#             */
/*   Updated: 2023/05/18 18:50:47 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_error(int error)

/*This function displays the different errors' messages that can be produced
during the program's execution.*/

{
	if (error == BAD_ARG)
		ft_printf("Error, bad numbers of arguments\n");
	else if (error == EXTENSION_ERROR)
		ft_printf("Error, the file's extension isn't .ber\n");
	else if (error == NOFILE_ERROR)
		ft_printf("Error, the file doesn't exist\n");
	else if (error == EMPTY_MAP)
		ft_printf("Error, the map is empty\n");
	else if (error == INVALID_MAP)
		ft_printf("Error, the map is invalid\n");
	else if (error == BAD_ROW)
		ft_printf("Error, the number of columns aren't the same for each row\n");
	else if (error == NO_WALLS)
		ft_printf("Error, the map isn't fully surrounded of walls\n");
	else if (error == INVALID_ELEMENT)
		ft_printf("Error, there is an undefied element in the map\n");
	else if (error == ELEMENT_ERROR)
		ft_printf("Error, the number of correct elements aren't invalid\n");
	else if (error == IMPOSIBLE_WIN)
		ft_printf("You can't win :(\n");
	exit(1);
}

/*This function frees the main structure of the program just before the
program's end:
1 - Free the strings that represent the rows of the map.
2 - Free the matrix itself, also in case it has been created but not filled.
3 - Free the string where the name of the map has been stored. 
4 - Free the structure.*/

void	ft_free(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->num_row)
	{
		free(game->map[i]);
		free(game->map_copy[i]);
		i++;
	}
	if (game->map)
	{
		free(game->map);
		free(game->map_copy);
	}
	free(game->map_name);
	free(game);
}

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
	/*ft_printf("map_copy:\n");
	while (game->map_copy[i])
	{
		ft_printf("%s\n", game->map_copy[i]);
		i++;
	}*/
}
