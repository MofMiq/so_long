/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_n_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:00:21 by marirodr          #+#    #+#             */
/*   Updated: 2023/05/12 17:57:42 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_error(int error)
{
	if (error == NOFILE_ERROR)
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
	exit(1);
}

void	ft_free(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->num_row) //liberas los strings que vienen a ser las row del mapa
	{
		free(game->map[i]);
		free(game->map_copy[i]);
		i++;
	}
	if (game->map) //liberas la matriz en si, tambien por si se ha creado la matriz pero no se ha rellanado
	{
		free(game->map);
		free(game->map_copy);
	}
	free(game->map_name); //liberar el string en el que se ha guardado el nombre del mapa
	free(game); //liberar la estructura
}
