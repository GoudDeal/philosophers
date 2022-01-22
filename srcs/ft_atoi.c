/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:50:11 by dcyprien          #+#    #+#             */
/*   Updated: 2022/01/22 15:08:45 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_cinset(const char c, const char *set)
{
	int	i;

	if (set != NULL)
	{
		i = 0;
		while (set[i])
		{
			if (c == set[i])
				return (1);
			i++;
		}
		return (0);
	}
	return (-1);
}

int	ft_isspace(const char c)
{
	return (ft_cinset(c, "\t\n\r\v\f "));
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;

	if (str != NULL)
	{
		result = 0;
		while (ft_isspace(*str))
			str++;
		if (str[0] == '-')
			i = 1;
		else
			i = 0;
		while (str[i] && ft_isdigit(str[i]) != 0)
			result = result * 10 + (str[i++] - '0');
		if (str[0] == '-')
			return (result * -1);
		return (result);
	}
	return (0);
}
