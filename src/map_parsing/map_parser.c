/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 00:25:42 by manuelma          #+#    #+#             */
/*   Updated: 2025/09/29 15:50:04 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"
#include "../../headers/debug.h"

/**
 * @brief checks that the file path is at least a char followed by '.cub'
 * @param file_path the map file path
 * @return ERR_FILE_NAME in case of error or SUCCESS
 */
int	check_file_path(char *file_path)
{
	int	i;

	i = ft_strlen(file_path);
	if (i <= 4)
		return (ERR_FILE_NAME);
	if (file_path[i - 4] != '.' || file_path[i - 3] != 'c' \
		|| file_path[i - 2] != 'u' || file_path[i - 1] != 'b')
		return (ERR_FILE_NAME);
	return (SUCCESS);
}

/**
 * @brief reads the map file, checks for errors and stores data
 * @param file_path the map file path
 * @param map_data the structure where we store the map data
 * @return e_num with specified error or success flag
 */
int	map_parser(char *file_path, t_map_data *map_data)
{
	char	**file_lines;
	int		last_param_index;

	if (check_file_path(file_path) != SUCCESS)
		return (ERR_FILE_NAME);
	file_lines = get_file_lines(file_path);
	if (file_lines == NULL)
		return (ERR_READ);
	last_param_index = get_map_param(file_lines, map_data);
	if (last_param_index == -1)
		return (free_double((void ***)&file_lines), ERR_MISS_OR_INVAL_PARAM);
	//check and store map after last_param_index
	// ---- for debug purposes ----
	printf("SUCCESS !\n");
	map_data->map = &(file_lines[last_param_index + 1]);
	print_map_data(map_data);
	// ----------------------------
	free_double((void ***)&file_lines);
	return (SUCCESS);
}
