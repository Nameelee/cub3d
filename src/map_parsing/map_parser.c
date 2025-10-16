/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 00:25:42 by manuelma          #+#    #+#             */
/*   Updated: 2025/09/30 20:36:59 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief Nami added. Takes a jagged 2D map and makes it rectangular.
 * @brief Each line in the new map is padded with spaces to match the
 * @brief maximum width. The original map is freed.
 * @param original_map The original map with uneven line lengths.
 * @param width The target width for the new rectangular map.
 * @param height The height of the map (number of lines).
 * @return A new, rectangular char ** map, or NULL on malloc failure.
 */
char	**regularize_map(char **original_map, int width, int height)
{
	char	**new_map;
	int		y;

	new_map = malloc(sizeof(char *) * (height + 1));
	if (!new_map)
		return (NULL);
	y = 0;
	while (y < height)
	{
		new_map[y] = malloc(sizeof(char) * (width + 1));
		if (!new_map[y])
		{
			free_double((void ***)&new_map);
			return (NULL);
		}
		ft_memset(new_map[y], ' ', width);
		ft_memcpy(new_map[y], original_map[y], ft_strlen(original_map[y]));
		new_map[y][width] = '\0';
		y++;
	}
	new_map[y] = NULL;
	free_double((void ***)&original_map);
	return (new_map);
}

/**
 * @brief stores the map lines in the map data structure
 * @param line_i the line index of the last saved parametter
 * @param file_lines the lines read from the map file
 * @param map_data the data where to store the map
 * @return enum with error code
 */
int	store_map(int line_i, char **file_lines, t_map_data *map_data)
{
	int	start_map_i;
	int	map_i;

	while (file_lines[line_i]
		&& str_is_only_isspace_or_empty(file_lines[line_i]))
		line_i++;
	start_map_i = line_i;
	while (!str_is_only_isspace_or_empty(file_lines[line_i]))
		line_i++;
	map_data->map = malloc(sizeof(char **) * ((line_i - start_map_i) + 1));
	if (map_data->map == NULL)
		return (ERR_MALLOC);
	map_i = 0;
	while (start_map_i < line_i)
	{
		map_data->map[map_i++] = ft_strdup(file_lines[start_map_i++]);
		if (map_data->map[map_i - 1] == NULL)
			return (ERR_MALLOC);
	}
	map_data->map[map_i] = NULL;
	while (file_lines[start_map_i])
		if (!str_is_only_isspace_or_empty(file_lines[start_map_i++]))
			return (ERR_MISS_OR_INVAL_PARAM);
	return (SUCCESS);
}

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
 * Nami add after 'error = store_map' till 'error = mapcheck' 
 * @param file_path the map file path
 * @param map_data the structure where we store the map data
 * @return e_num with specified error or success flag
 */
int	map_parser(char *file_path, t_map_data *map_data)
{
	char	**file_lines;
	int		last_param_index;
	int		error;

	if (check_file_path(file_path) != SUCCESS)
		return (ERR_FILE_NAME);
	file_lines = get_file_lines(file_path);
	if (file_lines == NULL)
		return (ERR_READ);
	last_param_index = 0;
	error = get_map_param(file_lines, map_data, &last_param_index);
	if (error != SUCCESS)
		return (free_double((void ***)&file_lines), error);
	if (last_param_index == -1 || !check_textures_file(map_data))
		return (free_double((void ***)&file_lines), ERR_MISS_OR_INVAL_PARAM);
	error = store_map(last_param_index, file_lines, map_data);
	if (error == SUCCESS)
	{
		map_data->height = 0;
		while (map_data->map[map_data->height])
			map_data->height++;
		map_data->width = get_map_width(map_data->map);
		map_data->map = regularize_map(map_data->map,
				map_data->width, map_data->height);
		if (!map_data->map)
			error = ERR_MALLOC;
		else
			error = map_checker(map_data);
	}
	free_double((void ***)&file_lines);
	return (error);
}
