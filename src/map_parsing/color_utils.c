/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:47:42 by manuelma          #+#    #+#             */
/*   Updated: 2025/09/29 15:49:00 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief checks that input contains valid color data
 * @param color string begining with color data
 * @return 1 if valid else 0
 */
int	is_valid_color_data(char *color)
{
	int	i;
	int digit_cnt;
	int	color_cnt;

	i = 0;
	color_cnt = 0;
	while (color[i])
	{
		digit_cnt = cnt_digits(&(color[i]));
		if (digit_cnt > 3 || digit_cnt == 0)
			return (0);
		color_cnt+=1;
		i += digit_cnt;
		i = next_index_after_isspace(color, i);
		if ((color_cnt < 3 && color[i] != ',') 
			|| (color_cnt >= 3 && color[i] == ','))
			return (0);
		if (color[i] == ',')
			i++;
		i = next_index_after_isspace(color, i);
	}
	if (color_cnt != 3)
		return (0);
	return (1);
}

/**
 * @brief extract the color value after a number of commas in 'input'
 * @param input the string begining with the color data
 * @param n_commas the number of commas to skip before getting the value
 * @return the value extracted and converted
 */
int	get_color_value_after_n_commas(char *input, int n_commas)
{
	int	i;
	int	commas_cnt;
	int	output;

	commas_cnt = 0;
	i = 0;
	while (input[i] && commas_cnt < n_commas)
	{
		if (input[i++] == ',')
			commas_cnt++;
	}
	i += get_index_after_isspace(&(input[i]));
	while (ft_isdigit(input[i]))
		i++;
	output = input[--i] - '0';
	if (ft_isdigit(input[--i]))
	{
		output += (input[i] - '0') * 10;
		if (ft_isdigit(input[--i]))
			output += (input[i] - '0') * 100;
	}
	return (output);
}

/**
 * @brief checks that input contains valid color data and extracts it
 * @param color string begining with color data
 * @param malloc_err_flag flag put to 1 to report a malloc error
 * @return color structure allocated with values or NULL in case of an error
 */
t_color *extract_color(char *color, int *malloc_err_flag)
{
	t_color			*output_color;

	if (!is_valid_color_data(color))
		return (NULL);
	if ((get_color_value_after_n_commas(color, 0) > 255)
		|| (get_color_value_after_n_commas(color, 1) > 255)
		|| (get_color_value_after_n_commas(color, 2) > 255))
		return (NULL);
	output_color = malloc(sizeof(t_color));
	if (!output_color)
	{
		*malloc_err_flag = 1;
		return (NULL);
	}
	output_color->r = (unsigned char)get_color_value_after_n_commas(color, 0);
	output_color->g = (unsigned char)get_color_value_after_n_commas(color, 1);
	output_color->b = (unsigned char)get_color_value_after_n_commas(color, 2);
	return (output_color);
}
