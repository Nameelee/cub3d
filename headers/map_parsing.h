/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 22:57:39 by manuelma          #+#    #+#             */
/*   Updated: 2025/09/30 20:35:11 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_PARSING_H
# define MAP_PARSING_H

char	**get_file_lines(char *file_path);
int		map_parser(char *file_path, t_map_data *map_data);
int		ft_isspace(char c);
int		get_index_after_isspace(char *str);
t_color	*extract_color(char *color, int *malloc_err_flag);
int		get_map_param(char **file_lines, t_map_data *map_data, int *i_lines);
int		process_and_validate_map(t_map_data *map_data);

#endif