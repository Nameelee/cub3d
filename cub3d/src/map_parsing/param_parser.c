/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:32:55 by manuelma          #+#    #+#             */
/*   Updated: 2025/09/30 21:15:19 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief stores the texture that is in the line 'str' in map_data structure
 * @param direction N, S, E, W
 * @param str the line containing a texture
 * @param map_data the structure that contains the map data stored
 * @return SUCCESS if the texture is found did not exist already, else if
 * texture is already stored returns ERR_MISS_OR_INVAL_PARAM, and in case of
 * a malloc error, returns ERR_MALLOC
 */
int	store_texture(char direction, char *texture_path, t_map_data *map_data)
{
	int		texture_len;

	texture_len = 0;
	while (!ft_isspace(texture_path[texture_len]))
		texture_len++;
	if (direction == 'N' && map_data->wall_n_t == NULL)
		map_data->wall_n_t = ft_substr(texture_path, 0, texture_len);
	else if (direction == 'S' && map_data->wall_s_t == NULL)
		map_data->wall_s_t = ft_substr(texture_path, 0, texture_len);
	else if (direction == 'E' && map_data->wall_e_t == NULL)
		map_data->wall_e_t = ft_substr(texture_path, 0, texture_len);
	else if (direction == 'W' && map_data->wall_w_t == NULL)
		map_data->wall_w_t = ft_substr(texture_path, 0, texture_len);
	else
		return (ERR_MISS_OR_INVAL_PARAM);
	if (direction == 'N' && map_data->wall_n_t == NULL)
		return (ERR_MALLOC);
	if (direction == 'S' && map_data->wall_s_t == NULL)
		return (ERR_MALLOC);
	if (direction == 'E' && map_data->wall_e_t == NULL)
		return (ERR_MALLOC);
	if (direction == 'W' && map_data->wall_w_t == NULL)
		return (ERR_MALLOC);
	return (SUCCESS);
}

/**
 * @brief stores the color that is in the line 'str' in map_data structure
 * @param identifier F, C
 * @param color string begining with color data
 * @param map_data the structure that contains the map data stored
 * @return SUCCESS if the color is found did not exist already, else -1
 * (ERR_MALLOC if there is a malloc error)
 */
int	store_color(char identifier, char *color, t_map_data *map_data)
{
	int		malloc_err_flag;

	malloc_err_flag = 0;
	if (identifier == 'F' && map_data->floor_color == NULL)
		map_data->floor_color = extract_color(color, &malloc_err_flag);
	else if (identifier == 'C' && map_data->ceiling_color == NULL)
		map_data->ceiling_color = extract_color(color, &malloc_err_flag);
	else
		return (ERR_MISS_OR_INVAL_PARAM);
	if ((identifier == 'C' && map_data->ceiling_color == NULL)
		|| (identifier == 'F' && map_data->floor_color == NULL))
	{
		if (malloc_err_flag)
			return (ERR_MALLOC);
		return (ERR_MISS_OR_INVAL_PARAM);
	}
	return (SUCCESS);
}

/**
 * @brief stores the parametter that is in the line 'str' in map_data structure
 * @param str the line containing a parametter
 * @param map_data the structure that contains the map data stored
 * @return SUCCESS if the parametter is found did not exist already, else -1
 * (ERR_MALLOC if there is a malloc error)
 */
int	store_param(char *str, t_map_data *map_data)
{
	int	error;
	int	i;

	error = -1;
	i = 0;
	if ((!ft_strncmp(str, "NO", 2) || !ft_strncmp(str, "SO", 2)
			|| !ft_strncmp(str, "EA", 2) || !ft_strncmp(str, "WE", 2))
		&& ft_isspace(str[2]))
	{
		i = get_index_after_isspace(&(str[2])) + 2;
		error = store_texture(*str, &(str[i]), map_data);
	}
	else if ((str[0] == 'F' || str[0] == 'C') && ft_isspace(str[1]))
	{
		i = get_index_after_isspace(&(str[1])) + 1;
		error = store_color(*str, &(str[i]), map_data);
	}
	return (error);
}

/**
 * @brief gets the parameters of the map and returns the index of the last
 * parametter line
 * @param file_lines a double string containing each line of the map file
 * @param map_data the structure that contains the map data stored
 * @param i_lines the index of the last parametter line or -1 if there is too
 * much or not enough parametters
 * @return the index of the last parametter line or -1 if there is too much or
 * not enough parametters
 */
int	get_map_param(char **file_lines, t_map_data *map_data, int *i_lines)
{
	int	i_chars;
	int	nbr_of_param_found;
	int	error;

	*i_lines = 0;
	nbr_of_param_found = 0;
	while (file_lines[*i_lines] && nbr_of_param_found < EXPECTED_PARAM_NBR)
	{
		i_chars = get_index_after_isspace(file_lines[*i_lines]);
		if (i_chars != (int)ft_strlen(file_lines[*i_lines]))
		{
			error = store_param(&(file_lines[*i_lines][i_chars]), map_data);
			if (error == SUCCESS)
				nbr_of_param_found++;
			else if (error > 0)
				return (error);
		}
		*i_lines += 1;
	}
	if (nbr_of_param_found != EXPECTED_PARAM_NBR)
		return (ERR_MISS_OR_INVAL_PARAM);
	return (SUCCESS);
}
