/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:35:12 by manuel            #+#    #+#             */
/*   Updated: 2023/03/11 15:35:12 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
memset sets BYTES to the desired constant c. It is up to the
caller to know how many bytes to set, depending on the
underlying type of the array (ints, n must be adjusted with sizeof,
etcetc). returns a pointer to the destination where the memory was
set to the constant.

BASED ON THE WORK OF
https://github.com/FlavioAMiceli/libft/blob/master/ft_memset.c


MULTIPLY_CHAR

get word copies the word to a bigger size to be pasted all at once.
let's say we want to place the character 'a' on the array.
'a' in binary is  01100001
'a' << 8, moves the bites 8 points to the right:

'a' << 8 =  01100001 00000000
how to get 'a' on the first 8 bits again?, use bit OR (|);

'a' << 8 =  01100001 00000000
'a'      =           01100001
OR (new) =  01100001 01100001

'a' is copied and now can be pasted twice in one turn!

BUT, we have 4 byte integers, we can double this, how?
same logic, move << 16 and OR with the previous!

new << 16 = 01100001 01100001 00000000 00000000
new       =                   01100001 01100001
OR (newer)= 01100001 01100001 01100001 01100001

'a' is copied to the size of an int!!!!! 4x paste at once!!

it may be the case that if CPU is 64bit, it can paste 8x at once
(8x8). in that case, unsigned long will be 8 bytes!
So we check if that's the case: sizeof(word) > 4 (could be even higher,
but forget about 128bit CPUs for now......)

So... we could move 32 bits at once!!!!!!! But doing so may trigger
a compiler warning (strlen.c), so it's best to do it slowly :)
we do << 16 << 16 (same as 32) in two tranches:

newer         =                                     01100001 01100001
01100001 01100001
newer << 16   =                   01100001 01100001 01100001 01100001
00000000 00000000
newer << 16   = 01100001 01100001 01100001 01100001 00000000 00000000
00000000 00000000
OR newer      = 01100001 01100001 01100001 01100001 01100001 01100001
01100001 01100001


AAAANDDD BOOM, we copied the same char 'a' to 8 slots to be pasted at once!!!

SUUUUUU


Unrolling the loop 4 at a time provides efficiency gains for larger sizes
but reduces efficiency for lower
lower sizes will remained capped at the naive ft_memset level.
One can get the unrolling size dependent on the size of the input to memset
if it is small enough, we can improve efficiency at up to 4 size,
and then increase it as we go along.

TESTING loop unrolling after 4 still makes sense but the impact becomes
evermore neglectible and
i would need to do custom made unrolls for each number. I'll leave between
4 and 2. 2 allows for improved
efficiency for sizes from 16 to 32 (below that,
		function works as the regular implementation). loop of 4
only allows gains after sizes of 32 and most likely i'll be using the
function below that




bitmemcopy: the first while loop is used to align the position of the
string in memory with
the size of the copies we will make: data structure alignment and padding.
this is to ensure "natural alignment": 64 bit processor reads 8 bytes but
they have to be aligned
for maximum efficiency. first loop is to align the memory address where
we start super copying
with that boundary. So: our word is 8 bytes. 8 is 0b1000,
	to guarantee alignment, 7 is 0b111
while the address of the string starts on a value less than a multiple
of 8,
move it along and
place characters while you do it (you have to do it for efficiency,
		you may remove this condition
but may result in problems in the program and/or loss of eficiency)
32bit, multiples of 4, (4 x8bits) so we do this alignment everytime,
	regardless of the processor
same is done in strlen.c

NOTICE: imagine you declare a string: the first address is usually
aligned,
	the OS makes sure
to place that string in a naturally aligned place,
	meaning that memory may be scattered with
nulls (padding),
	so each new data structure that doesn't fit the natural alignment
	will create
"holes" in memory. Becase of this,
	the while loop inside the function may be rarely triggered
given the OS is placing this new string naturally aligned already with
 the architecture. Nevertheless
for safety reasons,
	it is best to keep the loop in there in case the OS doesn't place
	our string in a
naturally aligned place,
	to make sure we can mass copy from an aligned position everytime.
	otherwise
ALL OF THIS IS FOOR NOTHING CAUSE WE ARE NOT TAKING ADVANTAGE OF THE
CLOCK READING A BANK,
CPU will NEED MORE THAN ONE CLOCK CYCLE TO COPY OUR 8 BYTE CHARACTER :(

like reading a book: you can read page 1 and 2 at once, but page 2 and 3,
	you need to turn to read
CPU works the same way when acessing memory, can read 8 pages if aligned,
	must flip banks if not.

the loop compares the address of the string with the number we give it,
	size(natural alignment) - 1
so it will move along until the address starts at	size(natural alignment).
We use the AND bit
operation for this if AND is diferent than zero,
	than our address isn't aligned yet.
NOTE, this loop will run at most sizeof(natural alignment)
	- 1 times. Why? (64 bit) either the string
is already naturally aligned (0 loops) or is 1 beyond
	-> 7 moves to bring it to alignment.

after guaranteeing the alignment,
	we get into the brain of the function: CHARWORD_SET.

CHARWORD_SET

Assuming roll 4:
memset_4unrolled unrolls the loop in 4,
temp_len -> we unroll as many 32 groups we can. if dest is size100,
	we unroll 3 times 32+32+32=96
temp_len = len / 32 (sizeof word * 4, if word is size 8);

then, we unroll group between 8 and 32 manually in the function:
then, len = what is left after unrolling those 32 groups (using mod)
so if you 42 in total, set 32, there are 10 left.
temp_len = len /sizeof(word) = 1. Out of the 10,
	we can still do 1 single block of 8
do it manually, move the pointer
then LEN now is 10 % 8 -> 2 left that MUST  be set 1 by 1 in our main function.

back to main function, convert string to unsigned char
	* again: we will be placing one char
at a time. move pointer, reduce len, place one character at a time, go home :)

I adapted the unrolling to include 2 rolls and allow efficiency gains
below size 32,
	more below


LOOP_UNROLL
unrolls the loop in either 2 or 4, so every round of the loop, it place 8
chars
	* 2(4) = 16(32) chars
in one go. i experimented removing the unrolling: 1 unroll (8 at a time) i
mproves performance in
memory spaces smaller than 32 (the unroll space) but decreases performance
 for longer sets,
	maybe
varying the unrolling size will help to optimize for different sizes.
Improvement from unrolling the loop from 4 to 8 for size 10000 wasn't a lot
 vs the naive implementation
Again, could unroll there but it involves function real estate,
	good homework assignment though


SUMMARY

Pretty much the same code as source,
	apart from the loop unrolling to improve efficiency on smaller
sizes. Eternal gratitude to the OG code (link above) and google x'D
All in all, this approach is better than the naive one but.....
nevermind once you use the actual memset from string.h....
the compiler probably has resources to optimize that even further at the
assembly code level
once again..... this is still a great exercise!!!!
on a working envieronment one would use the library functions an not our own,
	so we always build
on previous work and use it as our foundation.

*/

#include "ft_memfunc.h"

static t_ulong	multiply_char(int c)
{
	t_ulong	word;

	word = (t_uchar)c;
	word = (word << 8) | word;
	word = (word << 16) | word;
	if (UL_SIZE > 4)
		word = ((word << 16) << 16) | word;
	return (word);
}

static t_uchar	*loop_unroll(
t_ulong *b, t_ulong word, size_t len, size_t roll)
{
	if (roll == 4)
	{
		while (len-- > 0)
		{
			b[0] = word;
			b[1] = word;
			b[2] = word;
			b[3] = word;
			b += 4;
		}
	}
	else
	{
		while (len-- > 0)
		{
			b[0] = word;
			b[1] = word;
			b += 2;
		}
	}
	return ((t_uchar *)b);
}

static t_uchar	*charword_set(
t_uchar *str, t_ulong word, size_t *len)
{
	size_t	temp_len;
	size_t	roll;

	roll = *len / UL_SIZE;
	if (roll >= 4)
		roll = 4;
	else
		roll = 2;
	temp_len = *len / (UL_SIZE * roll);
	str = loop_unroll((t_ulong *)str, word, temp_len, roll);
	*len %= UL_SIZE * roll;
	temp_len = *len / UL_SIZE;
	while (temp_len-- > 0)
	{
		*((t_ulong *)str) = word;
		str += UL_SIZE;
	}
	*len %= UL_SIZE;
	return (str);
}

void	*ft_memset(void *b, int c, size_t len)
{
	t_uchar	*str;
	t_ulong	word;

	str = (t_uchar *)b;
	if (len >= UL_SIZE * 2)
	{
		word = multiply_char(c);
		while (((t_ulong)str & (UL_SIZE - 1)) != 0)
		{
			*str++ = c;
			len--;
		}
		str = charword_set(str, word, &len);
	}
	while (len-- > 0)
		*str++ = c;
	return (b);
}
