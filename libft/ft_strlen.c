/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:53:19 by manuelma          #+#    #+#             */
/*   Updated: 2025/08/11 12:10:14 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
/*
//TEST
#include <stdio.h>
int main(int ac, char **av)
{
	if (ac > 1)
		printf("input is :%d characters long", ft_strlen(av[1]));
}*/
