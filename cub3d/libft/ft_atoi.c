/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 00:02:19 by manuelma          #+#    #+#             */
/*   Updated: 2025/08/14 18:22:47 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	char		*endp;
	long long	val;
	int			res;
	int			ok;

	endp = 0;
	val = 0;
	res = 0;
	ok = ft_strtoll((char *)str, &val, &endp);
	if (ok == 0)
		return (0);
	res = (int)val;
	return (res);
}
