/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_print_reverse_alphabet.c                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: viwalker <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/06/23 16:21:56 by viwalker       #+#    #+#                */
/*   Updated: 2026/06/23 16:29:18 by viwalker       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_print_reverse_alphabet(void)
{
	char	*c;
	int		i;

	i = 0;
	c = "zyxwvutsrqponmlkjihgfedcba";
	while (c[i] <= 'z')
	{
		write(1, &c[i], 1);
		i++;
	}
}
