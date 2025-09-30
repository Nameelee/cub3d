/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 00:25:42 by manuelma          #+#    #+#             */
/*   Updated: 2025/09/30 16:36:01 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"
#include "../../headers/debug.h"

/**
 * @brief checks that the textures file name is valid and accessible
 * @param texture_name contains all textures file names
 * @return 1 if all valid, else 0
 */
int	check_texture_file_name_and_access(char *texture)
{
	int	i_char;
	int	fd;

	fd = open(texture, O_RDONLY);
	if (fd >= 0)
		close(fd);
	else
		return (0);
	i_char = ft_strlen(texture);
	if (i_char < 5)
		return (0);
	if (ft_strncmp(&(texture[i_char - 4]), ".xpm", 5) != 0)
		return (0);
	return (1);
}

/**
 * @brief checks that the textures file names are valid
 * @param map_data contains all textures file names
 * @return 1 if all valid, else 0
 */
int	check_textures_file(t_map_data *map_data)
{
	if (!check_texture_file_name_and_access(map_data->wall_n_t))
		return (0);
	if (!check_texture_file_name_and_access(map_data->wall_s_t))
		return (0);
	if (!check_texture_file_name_and_access(map_data->wall_w_t))
		return (0);
	if (!check_texture_file_name_and_access(map_data->wall_e_t))
		return (0);
	return (1);
}

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
	if (file_path[i - 4] != '.' || file_path[i - 3] != 'c'
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
	if (last_param_index == -1 || !check_textures_file(map_data))
		return (free_double((void ***)&file_lines), ERR_MISS_OR_INVAL_PARAM);
	free_double((void ***)&file_lines);
	return (SUCCESS);
}
