/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_rev_int_tab.c                                    :+:    :+:           */
/*                                                      +:+                   */
/*   By: viwalker <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/06/25 16:25:01 by viwalker       #+#    #+#                */
/*   Updated: 2026/06/25 17:00:33 by viwalker       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
// #include <stdio.h>
void	ft_rev_int_tab(int *tab, int size)
{
	int	rev[size];
	int	i;

	i = 0;
	while (i < size)
	{
		rev[size - i -1] = tab[i];
		i = i +1;
	}
	i = 0;
	while (i < size)
	{
		tab[i] = rev[i];
		i = i +1;
	}
}
/*
int	main()
{
	 int myNumbers[] = {25, 50, 75, 100};

	 ft_rev_int_tab(myNumbers, 4);
		
	 printf("%d\n", myNumbers[0]);
	 printf("%d\n", myNumbers[1]);
	 printf("%d\n", myNumbers[2]);
	 printf("%d\n", myNumbers[3]);
	 return 0;


}
*/
