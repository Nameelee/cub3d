/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:22:19 by manuelma          #+#    #+#             */
/*   Updated: 2025/09/30 19:42:26 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_UTILS_H
# define STRING_UTILS_H

int		next_index_after_isspace(char *str, int i);
int		str_is_only_isspace_or_empty(char *str);
int		cnt_digits(char *str);
void	print_strs(char **strs);
int		count_strs(char **strs);

#endif