/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:01:15 by manuelma          #+#    #+#             */
/*   Updated: 2025/09/08 23:07:44 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/**
 * @brief free the memory pointed and sets it to NULL
 * Example: int *nbr -> ft_free((void **)&nbr)
 * @param ptr the address of the memory to free casted to (void **)
 */
void	n_free(void **ptr)
{
	if (!ptr || !*ptr)
		return ;
	free(*ptr);
	*ptr = NULL;
}

/**
 * @brief free the double pointer and sets all addresses to NULL
 * Example: char **strs -> ft_free_double((void ***)&strs)
 * @param ptr the address of the double pointer casted to (void ***)
 */
void	free_double(void ***ptr)
{
	int		i;

	if (*ptr == NULL)
		return ;
	i = -1;
	while ((*ptr)[++i])
		n_free((void **)&((*ptr)[i]));
	free(*ptr);
	*ptr = NULL;
}
