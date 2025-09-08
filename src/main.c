/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:14:38 by manuelma          #+#    #+#             */
/*   Updated: 2025/09/08 23:04:26 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	main(int ac, char **av)
{
	char **map;

	if (ac != 2 || !av[1] || !av[1][0])
		return (1);
	map = get_file_lines(av[1]);
	if (!map)
		ft_putstr_fd(MSG_ERR_FILE, STDERR_FILENO);
	print_strs(map);
	free_double((void ***)&map);
	return (0);
}
