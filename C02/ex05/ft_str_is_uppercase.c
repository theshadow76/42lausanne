/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_str_is_uppercase.c                               :+:    :+:           */
/*                                                      +:+                   */
/*   By: viwalker <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/06/30 15:02:23 by viwalker       #+#    #+#                */
/*   Updated: 2026/06/30 15:04:57 by viwalker       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_str_is_uppercase(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 1;
	if (str[i] == '\0')
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			i++;
		else
			return (0);
	}
	return (res);
}
