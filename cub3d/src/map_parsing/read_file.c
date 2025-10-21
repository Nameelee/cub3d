/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:43:05 by manuelma          #+#    #+#             */
/*   Updated: 2025/09/30 16:35:43 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief Can be used to count how many lines a file contains.
 * @param file_path the path for the file we want to open and count lines.
 * @return an int with the number of lines the file contains.
 */
int	count_file_lines(char *file_path)
{
	char	*temp;
	int		i;
	int		fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (-1);
	temp = get_next_line(fd);
	if (!temp)
		return (close(fd), 0);
	i = 1;
	while (temp)
	{
		free(temp);
		temp = get_next_line(fd);
		i++;
	}
	return (close(fd), i);
}

/**
 * @brief Reads a file and gets each of its lines.
 * @param file_path the path for the file we want the lines of.
 * @return a NULL terminated list of strings with each line of the file.
 */
char	**get_file_lines(char *file_path)
{
	char	**output;
	int		i;
	int		fd;
	int		line_cnt;

	line_cnt = count_file_lines(file_path);
	if (line_cnt < 1)
		return (NULL);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	output = malloc(sizeof(char *) * line_cnt);
	if (!output)
		return (close(fd), NULL);
	i = 0;
	output[i] = get_next_line(fd);
	while (output[i])
		output[++i] = get_next_line(fd);
	close(fd);
	return (output);
}
