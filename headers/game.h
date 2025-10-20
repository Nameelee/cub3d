/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelee <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:23:48 by jelee             #+#    #+#             */
/*   Updated: 2025/10/20 16:23:56 by jelee            ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "data.h"

int		close_game(t_game *game);
int		game_loop(t_game *game);
void	free_map_data(t_map_data *map_data);
int		init_all(t_game *game);
void	init_map_data(t_map_data *map_data);
void	draw_minimap(t_game *game);

#endif
