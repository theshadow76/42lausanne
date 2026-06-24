/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_print_alphabet.c                                 :+:    :+:           */
/*                                                      +:+                   */
/*   By: viwalker <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/06/23 15:08:19 by viwalker       #+#    #+#                */
/*   Updated: 2026/06/23 17:36:05 by viwalker       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

void	ft_print_alphabet(void)
{
	char	*c;
	int		i;

	i = 0;
	c = "abcdefghijklmnopqrstuvwxyz";
	while (c[i] <= 'z')
	{
		write(1, &c[i], 1);
		i++;
	}
}
