#ifndef _CRC32_H
#define _CRC32_H

#define unit32_t unsigned long int

int make_crc32_table();
unit32_t make_crc(unit32_t crc, unsigned char *string, unit32_t size);

#endif

