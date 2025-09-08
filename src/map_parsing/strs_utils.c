/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 23:00:29 by manuelma          #+#    #+#             */
/*   Updated: 2025/09/08 23:04:00 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

/**
 * @brief prints a list of strings
 * @param strs the list of strings we want to print
 */
void	print_strs(char **strs)
{
	int	i;

	i = -1;
	while (strs && strs[++i])
		ft_putstr_fd(strs[i], 1);
}
