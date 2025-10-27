/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:34:15 by jelee             #+#    #+#             */
/*   Updated: 2025/10/27 15:37:41 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

/**
t<<24: move bit of t as 24 unit to the left 
and makes all into bits and combine all and return just 1 number. 
couldn't understand
*/
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/**
 * draw one pixel on the screen
 * to do that this check the exact address of memory
 * buffer->data: begining address of image memory
 * y * buffer->size_l: calcul the y location
 * 	:size_l is the byte that takes a row of image
 *  :so y * buffer->size_l brings to the beginning adress
 * buffer->bpp / 8
 * 	 :bbp is bits per pixel so 32/8 = 4 byte
 */
void	put_pixel_to_image(t_img *buffer, int x, int y, int color)
{
	char	*dst;

	dst = (char *)buffer->data + (y * buffer->size_l + x * (buffer->bpp / 8));
	*(unsigned int *)dst = color;
}
