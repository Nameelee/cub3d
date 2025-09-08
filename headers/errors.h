/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 22:51:10 by manuelma          #+#    #+#             */
/*   Updated: 2025/09/09 01:09:27 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

// list of error flags
typedef enum e_error
{
	SUCCESS = 0,
	ERR_ARGS,
	ERR_READ
}	t_error;

# define MSG_ERR_ARGS "Error\nIncorrect args, you must add one argument\
with the map file !\n"
# define MSG_ERR_READ "Error\nThere was a problem reading the file !\n(file \
is empty or there was an error reading it)\n"

#endif