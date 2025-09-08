/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 22:51:22 by manuelma          #+#    #+#             */
/*   Updated: 2025/08/13 17:45:54 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **lst, void (*del)(void *))
{
	if (!*lst)
		return ;
	if (del)
		del((*lst)->content);
	n_free((void **)lst);
}
