/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_str_is_printable.c                               :+:    :+:           */
/*                                                      +:+                   */
/*   By: viwalker <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/06/30 15:05:44 by viwalker       #+#    #+#                */
/*   Updated: 2026/06/30 15:10:29 by viwalker       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_str_is_printable(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 1;
	if (str[i] == '\0')
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] >= 32 && str[i] <= 126)
			i++;
		else
			return (0);
	}
	return (res);
}
