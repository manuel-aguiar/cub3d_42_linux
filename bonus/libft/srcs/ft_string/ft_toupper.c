/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:13:19 by manuel            #+#    #+#             */
/*   Updated: 2023/03/11 15:13:19 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* bitwise manipulation to speed things up
A : 01000001
a : 01100001

same as tolower, 6th bit->index 5
so 1 << 5 is:

1:        00000001;

(1 << 0): 00000001;
(1 << 1): 00000010;
(1 << 2): 00000100;
(1 << 3): 00001000;
(1 << 4): 00010000;
(1 << 5): 00100000;   here the 6th bit becomes 1

~(1 << 5) inverts the 0s to 1s and 1s to 0s, so we get:

 (1 << 5): 00100000
~(1 << 5): 11011111

a :        01100001
~(1 << 5): 11011111
AND:       01000001

which equals "A", done!!!!


some extra BS: 1 << 5 = 20 in HEX, so 0x20
saving that operation, replace 1 << 5 with 0x20 x'D


IN REALITY, ASSEMBLY CODE IS SIMILAR TO -32, NOT NEEDED
GOOD FUN STILL

*/

#include "ft_string.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c & ~0x20);
	return (c);
}
