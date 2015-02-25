#include "crc32.h"

unit32_t crc32_table[256];  

int make_crc32_table()
{
	unit32_t c;
	int i = 0;
	int bit = 0;
	
	for(i = 0; i<256;i++)
	{
		c = (unit32_t)i;
		for(bit = 0;bit <8;bit++)
		{
			if(c&1)
			{
				c = (c>>1)^0xEDB88320;
			}
			else
			{
				c = c>>1;
			}
		}
		crc32_table[i]=c;
	}
}
unit32_t make_crc(unit32_t crc, unsigned char *string, unit32_t size)
{
	while(size--)
		crc = (crc >> 8)^(crc32_table[(crc ^ *string++) &0xff]);
	return crc;
}
