/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:14:38 by manuelma          #+#    #+#             */
/*   Updated: 2025/09/30 16:32:29 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	init_map_data(t_map_data *map_data)
{
	map_data->ceiling_color = NULL;
	map_data->floor_color = NULL;
	map_data->wall_n_t = NULL;
	map_data->wall_s_t = NULL;
	map_data->wall_e_t = NULL;
	map_data->wall_w_t = NULL;
	map_data->map = NULL;
}

void	free_map_data(t_map_data *map_data)
{
	n_free((void **)&map_data->wall_n_t);
	n_free((void **)&map_data->wall_s_t);
	n_free((void **)&map_data->wall_e_t);
	n_free((void **)&map_data->wall_w_t);
	n_free((void **)&map_data->ceiling_color);
	n_free((void **)&map_data->floor_color);
	free_double((void ***)&map_data->map);
}

void	print_error(int error)
{
	if (error == ERR_ARGS)
		ft_putstr_fd(MSG_ERR_ARGS, STDERR_FILENO);
	else if (error == ERR_READ)
		ft_putstr_fd(MSG_ERR_READ, STDERR_FILENO);
	else if (error == ERR_FILE_NAME)
		ft_putstr_fd(MSG_ERR_FILE_NAME, STDERR_FILENO);
	else if (error == ERR_MISS_OR_INVAL_PARAM)
		ft_putstr_fd(MSG_ERR_MISS_OR_INVAL_PARAM, STDERR_FILENO);
	else if (error == ERR_MALLOC)
		ft_putstr_fd(MSG_ERR_MALLOC, STDERR_FILENO);
}

int	main(int ac, char **av)
{
	int			error;
	t_map_data	map_data;

	if (ac != 2 || !av[1] || !av[1][0])
		return (print_error(ERR_ARGS), 1);
	init_map_data(&map_data);
	error = map_parser(av[1], &map_data);
	if (error != SUCCESS)
		return (free_map_data(&map_data), print_error(error), 1);
	free_map_data(&map_data);
	return (0);
}
