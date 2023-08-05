#ifndef TYPES_H
#define TYPES_H

/* Instead of using 'chars' to allocate non-character bytes,
 * we will use these new type with no semantic meaning */
typedef unsigned int   uint32_t;
typedef          int   int32_t;
typedef unsigned short uint16_t;
typedef          short int16_t;
typedef unsigned char  uint8_t;
typedef          char  int8_t;

#define low_16(address) (uint16_t)((address) & 0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)
#define low_8(address) (uint8_t)((address) & 0xFF)
#define high_8(address) (uint8_t)(((address) >> 8) & 0xFF)
#endif