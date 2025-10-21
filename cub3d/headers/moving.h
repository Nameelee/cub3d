/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelee <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:25:49 by jelee             #+#    #+#             */
/*   Updated: 2025/10/20 16:25:52 by jelee            ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVING_H
# define MOVING_H

# include "data.h"

void	set_player_direction(t_game *game, char direction);
void	init_player_position(t_game *game);
void	move_player(t_game *game);

#endif
