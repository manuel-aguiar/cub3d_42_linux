/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:13:25 by manuel            #+#    #+#             */
/*   Updated: 2023/03/11 15:13:25 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* bitwise manipulation to speed things up
A : 01000001
a : 01100001

so lower is the same as upper with 6th bit turned to "1";
use bitwise OR ("|") with that particular bit. 6th bit->index 5
so 1 << 5 is:

1:        00000001;

(1 << 0): 00000001;
(1 << 1): 00000010;
(1 << 2): 00000100;
(1 << 3): 00001000;
(1 << 4): 00010000;
(1 << 5): 00100000;   here the 6th bit becomes 1

so A | (1 << 5) is equal to:

A :        01000001
(1 << 5) : 00100000
OR:        01100001

which equals "a", done!!!!


some extra BS: 1 << 5 = 20 in HEX, so 0x20
saving that operation, replace 1 << 5 with 0x20 x'D

IN REALITY, ASSEMBLY CODE IS SIMILAR TO +32, NOT NEEDED
GOOD FUN STILL

*/

#include "ft_string.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c | 0x20);
	return (c);
}
