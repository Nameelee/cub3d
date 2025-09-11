/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:56:14 by manuelma          #+#    #+#             */
/*   Updated: 2025/09/11 20:11:43 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	print_color(t_color *color, char c_f)
{
	if (c_f == 'C')
		printf("ceiling_color = ");
	else
		printf("floor_color = ");
	printf("%u,%u,%u\n", color->r, color->g, color->b);
}

void	print_map_data(t_map_data *map_data)
{
	int	i;

	print_color(map_data->ceiling_color, 'C');
	print_color(map_data->floor_color, 'F');
	printf("wall_n_t = %s\n", map_data->wall_n_t);
	printf("wall_s_t = %s\n", map_data->wall_s_t);
	printf("wall_w_t = %s\n", map_data->wall_w_t);
	printf("wall_e_t = %s\n", map_data->wall_e_t);
	printf("============== MAP ==============\n");
	i = 0;
	while (map_data->map[i])
		printf("%s\n", map_data->map[i++]);
	printf("=================================\n");
}
