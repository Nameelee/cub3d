/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelma <manuelma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:41:37 by manuelma          #+#    #+#             */
/*   Updated: 2025/08/14 18:24:02 by manuelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief vérifie si l'ajout du prochain chiffre fait un overflow
 * @param v valeur actuelle de la conversion
 * @param dg prochain chiffre à ajouter à la conversion
 * @param lmt la limite max ou min qu'on compare
 * @return 0 si overflow 1 si pas d'overflow
 */
int	overflow(unsigned long long *v, unsigned int dg, unsigned long long lmt)
{
	unsigned long long	tmp;

	tmp = *v;
	if (tmp > (lmt - dg) / 10)
		return (0);
	tmp = tmp * 10 + (unsigned long long)dg;
	*v = tmp;
	return (1);
}

/**
 * @brief lit les chiffres depuis 'str' et les convertis dans 'val', détecte si
 * il y a un overflow avec la fonction du même nom, et arrêtte la conversion si
 * c'est le cas. en cas d'overflow skip le reste du string à convertir.
 * @param str pointeur vers le string à convertir
 * @param sing 1 -> on converti un chiffre positif, -1 il est négatif
 * @param val pointeur ou l'on stocke la conversion en long long
 * @param overflowed flag de détection d'overflow (ou underflow)
 * @return 0 si aucun chiffre n'a pu etre converti 1 si conversion au moins
 * partiellement réussie
 */
int	rd_dg_ull(char **str, int sign, unsigned long long *val, int *overflowed)
{
	unsigned long long	limit;
	int					out;

	*val = 0;
	*overflowed = 0;
	out = 0;
	if (sign == 1)
		limit = (unsigned long long)LONG_MAX;
	else
		limit = (unsigned long long)LONG_MIN;
	while (**str >= '0' && **str <= '9')
	{
		out = 1;
		if (!overflow(val, (unsigned int)(**str - '0'), limit))
		{
			*overflowed = 1;
			while (**str >= '0' && **str <= '9')
				*str += 1;
			break ;
		}
		*str += 1;
	}
	return (out);
}

/**
 * @brief Finalise la valeur convertie en fonction du signe.
 * Si overflow != 0 → fixe errno et renvoie LLONG_MAX ou LLONG_MIN.
 * @param sign Signe de la valeur (+ -> +1, - -> -1)
 * @param v Valeur absolue non signée
 * @param overflowed Indique si un overflow à été détecté
 * @param out Pointeur qui stocke le resultat de la conversion
 */
int	end_signed(int sign, unsigned long long v, int overflowed, long long *out)
{
	if (overflowed)
	{
		errno = ERANGE;
		if (sign == 1)
			*out = LLONG_MAX;
		else
			*out = LLONG_MIN;
		return (1);
	}
	if (sign == 1)
	{
		*out = (long long)v;
		return (1);
	}
	if (v == (unsigned long long)LONG_MIN)
	{
		*out = LLONG_MIN;
		return (1);
	}
	*out = -(long long)v;
	return (1);
}

/**
 * @brief Convertit les chiffres à partir de *str en un long long signé.
 * Appelle rd_dg_ull pour lire les chiffres et end_signed pour finaliser.
 * @param str  Pointeur sur la chaîne à convertir (sera avancé)
 * @param sign Signe de la valeur (+1 ou -1)
 * @param out  Pointeur où stocker le résultat signé
 * @return 1 si conversion réussie, 0 si aucun chiffre lu
 */
int	convert_digits(char **str, int sign, long long *out)
{
	unsigned long long	v;
	int					ovf;
	int					have;

	ovf = 0;
	have = rd_dg_ull(str, sign, &v, &ovf);
	if (have == 0)
		return (0);
	return (end_signed(sign, v, ovf, out));
}

/**
 * @brief Conversion style strtoll() : convertit une chaîne ASCII en long long.
 * Ignore les espaces, lit le signe, convertit les chiffres, et fixe
 * errno=ERANGE si overflow/underflow.
 * @param str Chaîne à convertir
 * @param out Pointeur où stocker le résultat
 * @param endptr Pointeur qui recevra l'adresse où la lecture s'est arrêtée
 * @return 1 si conversion au moins partielle, sinon 0
 */
int	ft_strtoll(char *str, long long *out, char **endptr)
{
	int		sign;
	int		ok;

	errno = 0;
	str = ft_skip_spaces(str);
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	ok = convert_digits(&str, sign, out);
	if (endptr != 0)
		*endptr = str;
	return (ok);
}
