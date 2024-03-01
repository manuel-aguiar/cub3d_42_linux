/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_door.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:16:49 by marvin            #+#    #+#             */
/*   Updated: 2024/02/12 20:16:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "xpm_parser.h"

/* XPM */
char *g_door[] = {
/* columns rows colors chars-per-pixel */
"42 42 34 1 ",
"  c #000000",
". c #300D01",
"X c #2B1300",
"o c #351204",
"O c #391606",
"+ c #3E1B08",
"@ c #3F1C09",
"# c #471703",
"$ c #401F0A",
"% c #42210A",
"& c #45250B",
"* c #48290C",
"= c #4C2E0C",
"- c #57270E",
"; c #4C2A10",
": c #4D2A10",
"> c #513012",
", c #533313",
"< c #553316",
"1 c #5A3817",
"2 c #5E3E1A",
"3 c #653515",
"4 c #61421B",
"5 c #64461B",
"6 c #684B1B",
"7 c #76471B",
"8 c #7E5320",
"9 c #845A22",
"0 c #8D6626",
"q c #987527",
"w c #A58628",
"e c #C8BAB4",
"r c #D1C3B9",
"t c #DACEBD",
/* pixels */
"%=O+.%%$++o.o.%O+.o%&....%..++.O%..O+%O++%",
"%%%O.%++++ooO.+++OO%%.*.*%..+O+....OO%++O.",
"+&93#-##77##-3qw3777797#w3##7#78#7773w97+o",
"+.038#-9##3w#7#378877q#q#-3###77#9w#7#w0+.",
"..#3XXXXXwXXXXX#XXXXXqqw#330#-79#9w#9##7++",
"+&30X   XwX   X#X   X97q#-#q#79989w-77##%O",
"%%--X   X3X   X3X   X73w##qq#7979q-337-#%o",
"%O--X   X9X   X-X   X0w###30-9773#779#7-..",
".+-qX   X9X   X-X   X3q#3q#838797#7707#3..",
".O79X   X7X   X3X   X0#7#0#7##998#7789-3.+",
".O78X   X3X   X7X   Xq#7q837#390#99#887-.+",
"..3#X   X#X   X7X   X00#9937#7373-99#893.+",
"..##X   X3X   X7X   X#738737#0#37-79#9q3.%",
"..##X   X#X   X7X   X#779#79#0#39#9739w#.%",
".%73X   X#X   X7X   X3#073q7-7#39#9779w#O%",
".=73X   X#X   X7X   X7#9#0070733799770w-O+",
".=77X   X#X   X9X   X9-#077#q99-9#9078#3Oo",
"O*97X   X#X   X3X   X0#79#7#79###7#93#33%.",
"%.##X   X3X   X#X   X##3##7qq##-#7#3339-+O",
"%%93X   X3X   X#X   Xw09##qqq7-7#93077q9+$",
".%97X   X#X   X#X   X09w#9079-77#7#09999O=",
"o%97X   X8X   X-X   X9-w#8777#77:<:2>>>>o=",
"..97X   X8X   X7X   X9#9##77777#1retttt@..",
".O93X   X7X   X3X   X377##9-#3#76#:4>et:O.",
".+-9X   X-X   X9X   X-97--33#--7q-35@>>>O.",
".*w9X   X#X   X9X   X#0777#737#73###0979O.",
".*98X   X7X   X8X   X#03#9#09-38#w0#q8#9O+",
"+&97X   X7X   X0X   X37##730070##q079797$O",
"%Ow7X   X3X   X0X   Xw7#33#7809#qq7#937#%+",
"%.w7X   X3X   X9X   X#973-9#7-#-qq7#O#77O%",
"+.77X   X7X   X9X   X39#3390#3#3q7-7O377$+",
"%+#qX   X#X   X#X   X99#-w379q-09373#337&.",
"++3qX   X#X   X#X   X77##97-7q#7q73#7##9%.",
".+7#X   X-X   XwX   X93##979#3##q8##7w##.%",
"%+7#X   X9X   XwX   X993#q97#9##99#8#w77%%",
"+.7-X   X7X   XwX   X70#-w99#77##-#77777%+",
"+%#7X   X8X   X9X   X09#0q79377#37#0q-33++",
"O+#8XXXXX9XXXXX7XXXXX377www#077#7397q3#9o%",
"++w3#79-7793777-7#q70793www#q-7#7#990#0w.+",
"++0#7w90999#777#3#--#7q3ww7937808989##0w.$",
"++%O+o+%+%%++++Ooo%%%O*.%=O&.o%%O*+O.O+=+$",
"+.OO+...++O...+OO%%%+O&.%O+%..%.+=+..$+%%+"
};